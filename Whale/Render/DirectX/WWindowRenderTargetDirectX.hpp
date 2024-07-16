//
// Created by admin on 2024/7/16.
//

#pragma once

#include "Whale/Render/Utility/WRenderTarget.hpp"
#include "FDirectXHeader.hpp"

namespace Whale
{
	
	///
	/// 窗口渲染目标
	class WHALE_API WWindowRenderTargetDirectX : public WWindowRenderTarget
	{
	public:
		
		///
		/// 创建
		/// \param window 渲染窗口
		void Create(const Win32::WWindow &window) override;
	
	protected:
		
		void OnRender() override;
	
	private:
		
		const uint32 nFrameBackBufCount = 3;
		
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> pID3D12RenderTargets;
		
		Microsoft::WRL::ComPtr<IDXGISwapChain3> pIDXGISwapChain;
		
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> pID3D12RTVHeap;
		
		D3D12_VIEWPORT stViewPort;
		
		D3D12_RECT stScissorRect;
		
		uint32 nFrameIndex = 0;
		
	};
	
} // Whale
