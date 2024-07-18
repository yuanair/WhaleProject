//
// Created by admin on 2024/7/13.
//

#include "WRendererDirectX.hpp"

#include "WShaderDirectX.hpp"
#include "WWindowRenderTargetDirectX.hpp"
#include "WStaticMeshDirectX.hpp"

namespace Whale
{
	
	void WRendererDirectX::Create()
	{
		Microsoft::WRL::ComPtr<IDXGIAdapter1> pIAdapter;
		uint32 dxgiFactoryFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)
		EnableDebugLayer();
		dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif
		
		// 创建dxgi工厂
		THROW_IF_FAILED(
			CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&this->pIDXGIFactory))
		);
		
		// 遍历适配器
		for (UINT adapterIndex = 0;
		     DXGI_ERROR_NOT_FOUND != this->pIDXGIFactory->EnumAdapters1(adapterIndex, &pIAdapter); ++adapterIndex)
		{
			DXGI_ADAPTER_DESC1 desc{};
			pIAdapter->GetDesc1(&desc);
			// 软件虚拟适配器，跳过
			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;
			// 检查适配器对D3D支持的兼容级别，这里直接要求支持12.1的能力，注意返回接口的那个参数被置为了nullptr，这样
			// 就不会实际创建一个设备了，也不用我们啰嗦的再调用release来释放接口。这也是一个重要的技巧，请记住！
			if (
				SUCCEEDED(D3D12CreateDevice(pIAdapter.Get(), D3D_FEATURE_LEVEL_12_1, _uuidof(ID3D12Device), nullptr))
				)
				break;
			
		}
		// 创建D3D12.1的设备
		THROW_IF_FAILED(
			D3D12CreateDevice(pIAdapter.Get(), D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&this->pID3D12Device))
		);
		
		// 创建命令队列接口
		D3D12_COMMAND_QUEUE_DESC queueDesc
			{
				.Type = D3D12_COMMAND_LIST_TYPE_DIRECT
			};
		THROW_IF_FAILED(
			this->pID3D12Device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&this->pID3D12CommandQueue))
		);
		
		// 创建根描述符
		D3D12_FEATURE_DATA_ROOT_SIGNATURE stFeatureData = {};
		// 检测是否支持V1.1版本的根签名
		stFeatureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;
		if (FAILED(
			this->pID3D12Device->CheckFeatureSupport(
				D3D12_FEATURE_ROOT_SIGNATURE, &stFeatureData, sizeof(stFeatureData))))
		{
			stFeatureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_0;
		}
		// 在GPU上执行SetGraphicsRootDescriptorTable后，我们不修改命令列表中的SRV，因此我们可以使用默认Rang行为:
		// D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC_WHILE_SET_AT_EXECUTE
		CD3DX12_DESCRIPTOR_RANGE1 stDSPRanges[1];
		stDSPRanges[0].Init(
			D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC_WHILE_SET_AT_EXECUTE
		);
		
		CD3DX12_ROOT_PARAMETER1 stRootParameters[1];
		stRootParameters[0].InitAsDescriptorTable(1, &stDSPRanges[0], D3D12_SHADER_VISIBILITY_PIXEL);
		
		D3D12_STATIC_SAMPLER_DESC stSamplerDesc = {};
		stSamplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
		stSamplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
		stSamplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
		stSamplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
		stSamplerDesc.MipLODBias = 0;
		stSamplerDesc.MaxAnisotropy = 0;
		stSamplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
		stSamplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
		stSamplerDesc.MinLOD = 0.0f;
		stSamplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
		stSamplerDesc.ShaderRegister = 0;
		stSamplerDesc.RegisterSpace = 0;
		stSamplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		
		CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC stRootSignatureDesc;
		stRootSignatureDesc.Init_1_1(_countof(stRootParameters), stRootParameters, 1, &stSamplerDesc,
		                             D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
		);
		
		Microsoft::WRL::ComPtr<ID3DBlob> pISignatureBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> pIErrorBlob;
		THROW_IF_FAILED(D3DX12SerializeVersionedRootSignature(
			&stRootSignatureDesc, stFeatureData.HighestVersion, &pISignatureBlob, &pIErrorBlob
		));
		THROW_IF_FAILED(this->pID3D12Device->CreateRootSignature(
			0, pISignatureBlob->GetBufferPointer(), pISignatureBlob->GetBufferSize(),
			IID_PPV_ARGS(&this->pID3D12RootSignature)));
		
		// 得到每个描述符元素的大小
		this->nRTVDescriptorSize = this->pID3D12Device->GetDescriptorHandleIncrementSize(
			D3D12_DESCRIPTOR_HEAP_TYPE_RTV
		);
		
		// 创建命令列表分配器
		THROW_IF_FAILED(
			this->pID3D12Device->CreateCommandAllocator(
				D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&this->pID3D12CommandAllocator))
		);
		// 创建图形命令列表
		THROW_IF_FAILED(
			this->pID3D12Device->CreateCommandList(
				0, D3D12_COMMAND_LIST_TYPE_DIRECT, this->pID3D12CommandAllocator.Get(), nullptr,
				IID_PPV_ARGS(&this->pID3D12CommandList))
		);
		// 创建一个同步对象——围栏，用于等待渲染完成，因为现在Draw Call是异步的了
		THROW_IF_FAILED(
			this->pID3D12Device->CreateFence(
				0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&this->pID3D12Fence)));
		this->n64FenceValue = 1;
		// 创建一个Event同步对象，用于等待围栏事件通知
		this->hFenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		if (this->hFenceEvent == nullptr)
		{
			THROW_IF_FAILED(HRESULT_FROM_WIN32(GetLastError()));
		}
		
	}
	
	TFUniquePtr<WWindowRenderTarget> WRendererDirectX::CreateWindowRenderTarget()
	{
		return MakeUnique<WWindowRenderTargetDirectX>();
	}
	
	TFUniquePtr<WShader> WRendererDirectX::CreateShader()
	{
		return MakeUnique<WShaderDirectX>();
	}
	
	TFUniquePtr<WStaticMesh> WRendererDirectX::CreateStaticMesh()
	{
		return MakeUnique<WStaticMeshDirectX>();
	}
	
	void WRendererDirectX::EnableDebugLayer()
	{
#if defined(DEBUG) || defined(_DEBUG)
		THROW_IF_FAILED(D3D12GetDebugInterface(IID_PPV_ARGS(&this->pID3D12Debug)));
		this->pID3D12Debug->EnableDebugLayer();
#endif
	}
	
	void WRendererDirectX::Render()
	{
		for (auto &ptr: this->renderTargets)
		{
			ptr.Lock()->OnRender();
		}
	}
	
} // Whale