//
// Created by admin on 2024/7/30.
//

#pragma once

#include "HDirectXHeader.hpp"
#include <Whale/TIGPUResource.hpp>
#include <Whale/WObject.hpp>
#include "WRendererDirectX.hpp"

namespace Whale::DirectX
{
	
	/// 命令列表
	class WHALE_API WCommandListDirectX : public WObject, public TIGPUResource
	{
	public:
		
		explicit WCommandListDirectX(WRendererDirectX *pRenderer) : m_pRenderer(pRenderer) {}
	
	public:
		
		Bool Init() noexcept;
		
		Bool Run() noexcept;
		
		Bool Wait() noexcept;
		
		Bool Reset() noexcept;
	
	public:
		
		[[nodiscard]] Bool IsGPUResourceCreated() const noexcept override;
	
	private:
		
		void OnResourceDestroy() noexcept override;
		
		void OnEnable() noexcept override;
		
		void OnDisable() noexcept override;
	
	public:
		
		[[nodiscard]] auto &GetPID3D12CommandList() const { return m_pID3D12CommandList; }
		
		[[nodiscard]] auto &GetPID3D12CommandQueue() const { return m_pID3D12CommandQueue; }
	
	private:
		
		WRendererDirectX *m_pRenderer;
		
		Microsoft::WRL::ComPtr<ID3D12CommandQueue>        m_pID3D12CommandQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator>    m_pID3D12CommandAllocator;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_pID3D12CommandList;
		Microsoft::WRL::ComPtr<ID3D12Fence1>              m_pID3D12Fence;
		
		uint64 m_n64FenceValue = 0;
		HANDLE m_hFenceEvent   = nullptr;
		
	};
	
}
