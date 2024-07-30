//
// Created by admin on 2024/7/16.
//

#include "WWindowRenderTargetDirectX.hpp"
#include "WRendererDirectX.hpp"
#include "WCommandListDirectX.hpp"

namespace Whale::DirectX
{
	
	void WWindowRenderTargetDirectX::Create(const FWRTCreateArg &arg)
	{
		
		Microsoft::WRL::ComPtr<IDXGISwapChain1> pIDXGISwapChain;
		
		if (m_pRenderer == nullptr || !m_pRenderer->IsGPUResourceCreated())
		{
			FDebug::LogError(TagA, "m_pRenderer isn't create");
			return;
		}
		
		{
			auto rect = arg.m_window.GetRect();
			this->m_stScissorRect = CD3DX12_RECT{0, 0, rect.z() - rect.x(), rect.w() - rect.y()};
			this->m_stViewPort    = CD3DX12_VIEWPORT{
				0.0f, 0.0f, static_cast<float>(this->m_stScissorRect.right),
				static_cast<float>(this->m_stScissorRect.bottom)
			};
		}
		
		// 创建交换链
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc
			                      {
				                      .Width = (uint32) this->m_stScissorRect.right,
				                      .Height = (uint32) this->m_stScissorRect.bottom,
				                      .Format = DXGI_FORMAT_R8G8B8A8_UNORM,
				                      .Stereo = false,
				                      .SampleDesc = {.Count = 1, .Quality = 0},
				                      .BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
				                      .BufferCount = arg.m_frameBackBufferCount,
				                      .Scaling = DXGI_SCALING_STRETCH,
				                      .SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
				                      .AlphaMode = DXGI_ALPHA_MODE_IGNORE,
				                      .Flags = 0
			                      };
		
		THROW_IF_FAILED(
			m_pRenderer->GetPidxgiFactory()->CreateSwapChainForHwnd(
				m_pRenderer->GetPCommandList()->GetPID3D12CommandQueue().Get(),
				(HWND) arg.m_window.GetHWindow().handle,
				&swapChainDesc,
				nullptr,
				nullptr,
				&pIDXGISwapChain
			)
		);
		THROW_IF_FAILED(
			pIDXGISwapChain.As(&this->m_pIDXGISwapChain)
		);
		this->m_nFrameIndex = this->m_pIDXGISwapChain->GetCurrentBackBufferIndex();
		
		
		// 创建RTV描述符堆和RTV描述符
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
		rtvHeapDesc.NumDescriptors = arg.m_frameBackBufferCount;
		rtvHeapDesc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		
		THROW_IF_FAILED(
			m_pRenderer->GetPid3D12Device()->CreateDescriptorHeap(
				&rtvHeapDesc, IID_PPV_ARGS(this->pID3D12RTVHeap.ReleaseAndGetAddressOf()))
		);
		
		this->m_pID3D12RenderTargets.Relength(arg.m_frameBackBufferCount);
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(this->pID3D12RTVHeap->GetCPUDescriptorHandleForHeapStart());
		for (UINT                     i = 0; i < arg.m_frameBackBufferCount; i++)
		{
			THROW_IF_FAILED(
				this->m_pIDXGISwapChain->GetBuffer(
					i, IID_PPV_ARGS(
						this->m_pID3D12RenderTargets[i].ReleaseAndGetAddressOf()))
			);
			m_pRenderer->GetPid3D12Device()->CreateRenderTargetView(
				this->m_pID3D12RenderTargets[i].Get(), nullptr, rtvHandle
			);
			rtvHandle.Offset(1, m_pRenderer->GetRTVDescriptorSize());
		}
		
		
	}
	
	void WWindowRenderTargetDirectX::OnRender()
	{
		if (m_pRenderer == nullptr || !m_pRenderer->IsGPUResourceCreated())
		{
			FDebug::LogError(TagA, "m_pRenderer isn't create");
			return;
		}
		m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->SetGraphicsRootSignature(
			m_pRenderer->GetPid3D12RootSignature().Get());
		ID3D12DescriptorHeap *ppHeaps[] = {m_pRenderer->GetPSRVHeap().Get()};
		m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
		m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->SetGraphicsRootDescriptorTable(
			0, m_pRenderer->GetPSRVHeap()->GetGPUDescriptorHandleForHeapStart());
		m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->RSSetViewports(1, &this->m_stViewPort);
		m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->RSSetScissorRects(1, &this->m_stScissorRect);
		
		// 通过资源屏障判定后缓冲已经切换完毕可以开始渲染了
		auto resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
			this->m_pID3D12RenderTargets[this->m_nFrameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT,
			D3D12_RESOURCE_STATE_RENDER_TARGET
		);
		m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->ResourceBarrier(
			1, &resourceBarrier
		);
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(
			this->pID3D12RTVHeap->GetCPUDescriptorHandleForHeapStart(), static_cast<INT>(this->m_nFrameIndex),
			m_pRenderer->GetRTVDescriptorSize()
		);
		
		//设置渲染目标
		m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
		// 继续记录命令，并真正开始新一帧的渲染
		const float clearColor[] = {0.0f, 0.2f, 0.4f, 1.0f};
		m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->ClearRenderTargetView(
			rtvHandle, clearColor, 0, nullptr
		);
		
		// ...
		for (auto &item: this->m_renderObjects)
		{
			if (auto locked = item.Lock()) locked->Render();
		}
		
		//又一个资源屏障，用于确定渲染已经结束可以提交画面去显示了
		resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
			this->m_pID3D12RenderTargets[this->m_nFrameIndex].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET,
			D3D12_RESOURCE_STATE_PRESENT
		);
		m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->ResourceBarrier(
			1, &resourceBarrier
		);
		
		m_pRenderer->GetPCommandList()->Run();
		//关闭命令列表，可以去执行了
//		THROW_IF_FAILED(m_pRenderer->GetPid3D12CommandList()->Close());
//		//执行命令列表
//		ID3D12CommandList *ppCommandLists[] = {m_pRenderer->GetPid3D12CommandList().Get()};
//		m_pRenderer->GetPid3D12CommandQueue()->ExecuteCommandLists(1, ppCommandLists);
		
		//提交画面
		THROW_IF_FAILED(this->m_pIDXGISwapChain->Present(1, 0));
		m_pRenderer->GetPCommandList()->Wait();
//		//开始同步GPU与CPU的执行，先记录围栏标记值
//		const uint64 fence = m_pRenderer->GetN64FenceValue();
//		THROW_IF_FAILED(m_pRenderer->GetPid3D12CommandQueue()->Signal(m_pRenderer->GetPid3D12Fence().Get(), fence));
//		m_pRenderer->AddN64FenceValue();
//
//		// 看命令有没有真正执行到围栏标记的这里，没有就利用事件去等待，注意使用的是命令队列对象的指针
//		if (m_pRenderer->GetPid3D12Fence()->GetCompletedValue() < fence)
//		{
//			THROW_IF_FAILED(
//				m_pRenderer->GetPid3D12Fence()->SetEventOnCompletion(fence, m_pRenderer->GetHFenceEvent()));
//			WaitForSingleObject(m_pRenderer->GetHFenceEvent(), INFINITE);
//		}
		
		//到这里说明一个命令队列完整的执行完了，在这里就代表我们的一帧已经渲染完了，接着准备执行下一帧//渲染
		//获取新的后缓冲序号，因为Present真正完成时后缓冲的序号就更新了
		this->m_nFrameIndex = this->m_pIDXGISwapChain->GetCurrentBackBufferIndex();
		m_pRenderer->GetPCommandList()->Reset();
//		//命令分配器先Reset一下
//		THROW_IF_FAILED(m_pRenderer->GetPid3D12CommandAllocator()->Reset());
//		//Reset命令列表，并重新指定命令分配器和PSO对象
//		THROW_IF_FAILED(
//			m_pRenderer->GetPid3D12CommandList()->Reset(m_pRenderer->GetPid3D12CommandAllocator().Get(), nullptr));
	}
	
	void WWindowRenderTargetDirectX::OnEnable() noexcept
	{
	
	}
	
	void WWindowRenderTargetDirectX::OnDisable() noexcept
	{
	
	}
	
	Bool WWindowRenderTargetDirectX::IsGPUResourceCreated() const noexcept
	{
		return m_pIDXGISwapChain;
	}
	
	void WWindowRenderTargetDirectX::OnResourceDestroy() noexcept
	{
		m_pID3D12RenderTargets.Clear();
		m_pIDXGISwapChain.Reset();
		pID3D12RTVHeap.Reset();
		m_stViewPort = {};
		m_stScissorRect = {};
		m_nFrameIndex = 0;
	}
	
} // Whale