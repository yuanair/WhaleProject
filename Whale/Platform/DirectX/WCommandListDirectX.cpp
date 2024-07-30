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
	
	Bool WCommandListDirectX::IsGPUResourceCreated() const noexcept
	{
		return 0;
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