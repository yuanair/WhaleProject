//
// Created by admin on 2024/7/16.
//

#pragma once

#include "Whale/Platform/WWindowRenderTarget.hpp"
#include "HDirectXHeader.hpp"
#include "WRendererDirectX.hpp"

namespace Whale::DirectX
{
	
	///
	/// 窗口渲染目标
	class WHALE_API WWindowRenderTargetDirectX : public WWindowRenderTarget
	{
	public:
		
		explicit WWindowRenderTargetDirectX(WRendererDirectX *pRenderer) : m_pRenderer(pRenderer) {}
	
	public:
		
		void Create(const FWRTCreateArg &arg) override;
	
	private:
		
		void OnRender() override;
		
		void OnEnable() noexcept override;
		
		void OnDisable() noexcept override;
	
	private:
		
		WRendererDirectX *m_pRenderer;
		
		Container::TFArray<Microsoft::WRL::ComPtr<ID3D12Resource>> m_pID3D12RenderTargets;
		
		Microsoft::WRL::ComPtr<IDXGISwapChain3> m_pIDXGISwapChain;
		
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> pID3D12RTVHeap;
		
		D3D12_VIEWPORT m_stViewPort{};
		
		D3D12_RECT m_stScissorRect{};
		
		uint32 m_nFrameIndex = 0;
		
	};
	
} // Whale
