//
// Created by admin on 2024/7/9.
//

#pragma once


#include "Whale/Core/FUndefinedData.hpp"
#include "Whale/DirectX/FDirectXHeader.hpp"

#include <vector>

namespace Whale
{
	
	class WWindowRenderTargetDirectX12Data : public WObject
	{
	public:
		
		const uint32 nFrameBackBufCount = 3;
		
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> pID3D12RenderTargets;
		
		Microsoft::WRL::ComPtr<IDXGISwapChain3> pIDXGISwapChain;
		
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> pID3D12RTVHeap;
		
		D3D12_VIEWPORT stViewPort;
		
		D3D12_RECT stScissorRect;
		
		uint32 nFrameIndex = 0;
		
	};
}
