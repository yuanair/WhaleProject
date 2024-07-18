//
// Created by admin on 2024/7/13.
//

#pragma once

#include "Whale/Render/Utility/WRenderer.hpp"
#include "Whale/Core/Container/HMemory.hpp"
#include "Whale/Render/DirectX/HDirectXHeader.hpp"
#include "FWICForDirectX.hpp"

namespace Whale
{
	
	///
	/// DirectX渲染器
	class WHALE_API WRendererDirectX : public WRenderer
	{
	public:
		
		inline static std::string GetStaticNameA() { return "DirectX"; }
		
		inline static std::wstring GetStaticNameW() { return L"DirectX"; }
	
	public:
		
		void Create() override;
		
		TFUniquePtr<WWindowRenderTarget> CreateWindowRenderTarget() override;
		
		TFUniquePtr<WShader> CreateShader() override;
		
		TFUniquePtr<WStaticMesh> CreateStaticMesh() override;
		
		void Render() override;
	
	private:
		
		// 开启DirectX调试层
		void EnableDebugLayer();
	
	public:
		
		[[nodiscard]]
		inline ERendererType GetType() const override { return ERendererTypeDirectX; }
		
		[[nodiscard]]
		inline std::string GetNameA() const override { return GetStaticNameA(); }
		
		[[nodiscard]]
		inline std::wstring GetNameW() const override { return GetStaticNameW(); }
	
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
	
} // Whale
