//
// Created by admin on 2024/7/13.
//

#pragma once

#include "Whale/Platform/WRenderer.hpp"
#include "Whale/Core/Memory.hpp"
#include "HDirectXHeader.hpp"
#include "FWICForDirectX.hpp"

namespace Whale::DirectX
{
	
	///
	/// DirectX渲染器
	class WHALE_API WRendererDirectX : public WRenderer
	{
	public:
		
		void OnGPUCreate() noexcept override;
		
		void OnGPUDestroy() noexcept override;
		
		[[nodiscard]] Bool IsGPUResourceCreated() const noexcept override;
	
	private:
		
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

#if defined(DEBUG) || defined(_DEBUG)
		
		Microsoft::WRL::ComPtr<ID3D12Debug6> pID3D12Debug;

#endif
		
		Microsoft::WRL::ComPtr<IDXGIFactory7> pIDXGIFactory;
		
		Microsoft::WRL::ComPtr<ID3D12Device10> pID3D12Device;
		
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> pID3D12CommandQueue;
		
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> pID3D12CommandAllocator;
		
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> pID3D12CommandList;
		
		Microsoft::WRL::ComPtr<ID3D12RootSignature> pID3D12RootSignature;
		
		Microsoft::WRL::ComPtr<ID3D12Fence1> pID3D12Fence;
		
		//
		uint64 n64FenceValue = 0;
		
		//
		HANDLE hFenceEvent = nullptr;
		
		// 每个描述符元素的大小
		uint32 nRTVDescriptorSize = 0;
		
		// WIC
		FWICForDirectX wicForDirectX;
		
	};
	
} // Whale
