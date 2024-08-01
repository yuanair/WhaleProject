//
// Created by admin on 2024/7/30.
//

#include "WCommandListDirectX.hpp"

namespace Whale::DirectX
{
	Bool WCommandListDirectX::Init() noexcept
	{
		// 创建命令队列接口
		D3D12_COMMAND_QUEUE_DESC queueDesc
			                         {
				                         .Type = D3D12_COMMAND_LIST_TYPE_DIRECT
			                         };
		THROW_IF_FAILED(
			m_pRenderer->GetPid3D12Device()->CreateCommandQueue(
				&queueDesc, IID_PPV_ARGS(this->m_pID3D12CommandQueue.ReleaseAndGetAddressOf()))
		);
		
		// 创建命令列表分配器
		THROW_IF_FAILED(
			m_pRenderer->GetPid3D12Device()->CreateCommandAllocator(
				D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(this->m_pID3D12CommandAllocator.ReleaseAndGetAddressOf()))
		);
		// 创建图形命令列表
		THROW_IF_FAILED(
			m_pRenderer->GetPid3D12Device()->CreateCommandList(
				0, D3D12_COMMAND_LIST_TYPE_DIRECT, this->m_pID3D12CommandAllocator.Get(), nullptr,
				IID_PPV_ARGS(this->m_pID3D12CommandList.ReleaseAndGetAddressOf()))
		);
		// 创建一个同步对象——围栏，用于等待渲染完成，因为现在Draw Call是异步的了
		THROW_IF_FAILED(
			m_pRenderer->GetPid3D12Device()->CreateFence(
				0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(this->m_pID3D12Fence.ReleaseAndGetAddressOf())));
		this->m_n64FenceValue = 1;
		// 创建一个Event同步对象，用于等待围栏事件通知
		this->m_hFenceEvent   = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		if (this->m_hFenceEvent == nullptr)
		{
			THROW_IF_FAILED(HRESULT_FROM_WIN32(GetLastError()));
		}
		
		return true;
	}
	
	Bool WCommandListDirectX::Run() noexcept
	{
		//关闭命令列表，可以去执行了
		THROW_IF_FAILED(m_pID3D12CommandList->Close());
		//执行命令列表
		ID3D12CommandList *ppCommandLists[] = {m_pID3D12CommandList.Get()};
		m_pID3D12CommandQueue->ExecuteCommandLists(1, ppCommandLists);
		return true;
	}
	
	Bool WCommandListDirectX::Wait() noexcept
	{
		//开始同步GPU与CPU的执行，先记录围栏标记值
		const uint64 fence = m_n64FenceValue;
		THROW_IF_FAILED(m_pID3D12CommandQueue->Signal(m_pID3D12Fence.Get(), fence));
		++m_n64FenceValue;
		
		// 看命令有没有真正执行到围栏标记的这里，没有就利用事件去等待，注意使用的是命令队列对象的指针
		if (m_pID3D12Fence->GetCompletedValue() < fence)
		{
			THROW_IF_FAILED(
				m_pID3D12Fence->SetEventOnCompletion(fence, m_hFenceEvent));
			WaitForSingleObject(m_hFenceEvent, INFINITE);
		}
		return true;
	}
	
	Bool WCommandListDirectX::Reset() noexcept
	{
		//命令分配器先Reset一下
		THROW_IF_FAILED(m_pID3D12CommandAllocator->Reset());
		//Reset命令列表，并重新指定命令分配器和PSO对象
		THROW_IF_FAILED(
			m_pID3D12CommandList->Reset(m_pID3D12CommandAllocator.Get(), nullptr));
		return true;
	}
	
	Bool WCommandListDirectX::IsGPUResourceCreated() const noexcept
	{
		return m_pID3D12CommandList;
	}
	
	void WCommandListDirectX::OnResourceDestroy() noexcept
	{
	
	}
	
	void WCommandListDirectX::OnEnable() noexcept
	{
	
	}
	
	void WCommandListDirectX::OnDisable() noexcept
	{
	
	}
}