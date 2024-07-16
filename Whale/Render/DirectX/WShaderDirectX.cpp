//
// Created by admin on 2024/7/16.
//

#include "WShaderDirectX.hpp"


#include "Whale/Render/DirectX/WRendererDirectX.hpp"
#include "Whale/Core/Container/FTUniquePtr.hpp"

namespace Whale
{
	
	bool WShaderDirectX::CreateFromFile(const std::wstring &fileName)
	{
		auto &renderer = WRenderer::GetRenderer<WRendererDirectX>();
		
		Microsoft::WRL::ComPtr<ID3DBlob> pVertexShader;
		Microsoft::WRL::ComPtr<ID3DBlob> pPixelShader;
		Microsoft::WRL::ComPtr<ID3DBlob> pErrorMsgs;
#if defined(_DEBUG)
		uint32 compileFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		uint32 compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#endif
		
		bool isFailed = false;
		auto hr = D3DCompileFromFile(
			fileName.c_str(), nullptr, nullptr, "vertex", "vs_5_0", compileFlags, 0, &pVertexShader, &pErrorMsgs
		);
		if (FAILED(hr))
		{
			if (!pErrorMsgs) THROW_IF_FAILED(hr);
			FDebug::LogError(
				WProgram::GetAppNameA(),
				(
					std::string("Vertex Shader: ") +
					reinterpret_cast<const char *>(pErrorMsgs->GetBufferPointer())
				).c_str()
			);
			isFailed = true;
		}
		
		hr = D3DCompileFromFile(
			fileName.c_str(), nullptr, nullptr, "pixel", "ps_5_0", compileFlags, 0, &pPixelShader, &pErrorMsgs
		);
		if (FAILED(hr))
		{
			if (!pErrorMsgs) THROW_IF_FAILED(hr);
			FDebug::LogError(
				WProgram::GetAppNameA(),
				(
					std::string("Pixel Shader: ") +
					reinterpret_cast<const char *>(pErrorMsgs->GetBufferPointer())
				).c_str()
			);
			isFailed = true;
		}
		
		if (isFailed) return false;
		
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
			{
				{
					"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,
					D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
				},
				{
					"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * sizeof(float),
					D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
				}
				
			};
		
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		
		psoDesc.InputLayout = {inputElementDescs, _countof(inputElementDescs)};
		psoDesc.pRootSignature = renderer.pID3D12RootSignature.Get();
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(pVertexShader.Get());
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(pPixelShader.Get());
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable = FALSE;
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.SampleDesc.Count = 1;
		
		THROW_IF_FAILED(
			renderer.pID3D12Device->CreateGraphicsPipelineState(
				&psoDesc, IID_PPV_ARGS(&this->pID3D12PipelineState))
		);
		return true;
	}
	
	void WShaderDirectX::Use()
	{
		auto &renderer = WRenderer::GetRenderer<WRendererDirectX>();
		renderer.pID3D12CommandList->SetPipelineState(this->pID3D12PipelineState.Get());
	}
	
} // Whale