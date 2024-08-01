//
// Created by admin on 2024/7/13.
//

#pragma once

#include <Whale/WRenderer.hpp>
#include <Whale/Memory.hpp>
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
		
		~WRendererDirectX() override = default;
	
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
		
		[[nodiscard]] auto &GetPid3D12RootSignature() const noexcept { return m_pID3D12RootSignature; }
		
		[[nodiscard]] auto &GetPSRVHeap() const noexcept { return m_pSRVHeap; }
		
		[[nodiscard]] auto &GetPCommandList() const noexcept { return m_pCommandList; }
		
		[[nodiscard]] auto &GetPWICForDirectX() const noexcept { return m_pWICForDirectX; }
		
		[[nodiscard]] uint32 GetRTVDescriptorSize() const noexcept { return m_RTVDescriptorSize; }
	
	private:

#if defined(DEBUG) || defined(_DEBUG)
		
		Microsoft::WRL::ComPtr<ID3D12Debug6> m_pID3D12Debug;

#endif
		
		Microsoft::WRL::ComPtr<IDXGIFactory7> m_pIDXGIFactory;
		
		Microsoft::WRL::ComPtr<ID3D12Device10> m_pID3D12Device;
		
		Microsoft::WRL::ComPtr<ID3D12RootSignature> m_pID3D12RootSignature;
		
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_pSRVHeap;
		
		TFUniquePtr<WCommandListDirectX> m_pCommandList;
		
		TFUniquePtr<WWICForDirectX> m_pWICForDirectX;
		
		// 每个描述符元素的大小
		uint32 m_RTVDescriptorSize = 0;
		
	};
	
} // Whale
