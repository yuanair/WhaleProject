//
// Created by admin on 2024/7/9.
//

#pragma once

#include "Whale/Core/FUndefinedData.hpp"
#include "Whale/DirectX/FDirectXHeader.hpp"

#include "Whale/DirectX/FWICForDirectX.hpp"

namespace Whale
{
	class WDirectX12Data : public WObject
	{
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
		
		//
		FWICForDirectX wicForDirectX;
		
	};
}