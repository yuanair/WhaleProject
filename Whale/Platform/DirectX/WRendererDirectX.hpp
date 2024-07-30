//
// Created by admin on 2024/7/13.
//

#pragma once

#include "Whale/Platform/WRenderer.hpp"
#include "Whale/Core/Memory.hpp"
#include "HDirectXHeader.hpp"
#include "WWICForDirectX.hpp"

namespace Whale::DirectX
{
	
	class WCommandListDirectX;
	
	///
	/// DirectX渲染器
	class WHALE_API WRendererDirectX : public WRenderer
	{
	public:
		
		void Init() noexcept override;
		
		[[nodiscard]] Bool IsGPUResourceCreated() const noexcept override;
	
	private:
		
		void OnResourceDestroy() noexcept override;
		
		void OnRender() override;
		
		TFUniquePtr<WWindowRenderTarget> OnMakeWindowRenderTarget() override;
		
		TFUniquePtr<WShader> OnMakeShader() override;
		
		TFUniquePtr<WRenderingPipeline> OnMakeRenderingPipeline() override;
		
		TFUniquePtr<WMaterial> OnMakeMaterial() override;
		
		TFUniquePtr<WStaticMesh> OnMakeStaticMesh() override;
		
		TFUniquePtr<WBitmap> OnMakeBitmap() override;
		
		void OnEnable() noexcept override;
		
		void OnDisable() noexcept override;
	
	private:
		
		// 开启DirectX调试层
		void EnableDebugLayer();
	
	public:
		
		[[nodiscard]]
		inline ERendererType GetType() const override { return ERendererTypeDirectX; }
	
	public:
		
		[[nodiscard]] auto &GetPid3D12Debug() const noexcept { return m_pID3D12Debug; }
		
		[[nodiscard]] auto &GetPidxgiFactory() const noexcept { return m_pIDXGIFactory; }
		
		[[nodiscard]] auto &GetPid3D12Device() const noexcept { return m_pID3D12Device; }
		
		[[nodiscard]] auto &GetPid3D12CommandQueue() const noexcept { return m_pID3D12CommandQueue; }
		
		[[nodiscard]] auto &GetPid3D12CommandAllocator() const noexcept { return m_pID3D12CommandAllocator; }
		
		[[nodiscard]] auto &GetPid3D12CommandList() const noexcept { return m_pID3D12CommandList; }
		
		[[nodiscard]] auto &GetPid3D12RootSignature() const noexcept { return m_pID3D12RootSignature; }
		
		[[nodiscard]] auto &GetPid3D12Fence() const noexcept { return m_pID3D12Fence; }
		
		[[nodiscard]] auto &GetPWICForDirectX() const noexcept { return m_pWICForDirectX; }
		
		[[nodiscard]] uint64 GetN64FenceValue() const noexcept { return m_n64FenceValue; }
		
		[[nodiscard]] const HANDLE GetHFenceEvent() const noexcept { return m_hFenceEvent; }
		
		[[nodiscard]] uint32 GetRTVDescriptorSize() const noexcept { return m_RTVDescriptorSize; }
		
		void AddN64FenceValue() noexcept { ++m_n64FenceValue; }
	
	private:

#if defined(DEBUG) || defined(_DEBUG)
		
		Microsoft::WRL::ComPtr<ID3D12Debug6> m_pID3D12Debug;

#endif
		
		Microsoft::WRL::ComPtr<IDXGIFactory7> m_pIDXGIFactory;
		
		Microsoft::WRL::ComPtr<ID3D12Device10> m_pID3D12Device;
		
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_pID3D12CommandQueue;
		
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_pID3D12CommandAllocator;
		
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_pID3D12CommandList;
		
		Microsoft::WRL::ComPtr<ID3D12RootSignature> m_pID3D12RootSignature;
		
		Microsoft::WRL::ComPtr<ID3D12Fence1> m_pID3D12Fence;
		
		TFUniquePtr<WCommandListDirectX> m_pCommandList;
		
		TFUniquePtr<WWICForDirectX> m_pWICForDirectX;
		
		//
		uint64 m_n64FenceValue = 0;
		HANDLE m_hFenceEvent   = nullptr;
		
		// 每个描述符元素的大小
		uint32 m_RTVDescriptorSize = 0;
		
	};
	
} // Whale
