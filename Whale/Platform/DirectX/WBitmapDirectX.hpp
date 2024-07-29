//
// Created by admin on 2024/7/16.
//

#pragma once

#include "Whale/Platform/WBitmap.hpp"
#include "HDirectXHeader.hpp"
#include "WRendererDirectX.hpp"

namespace Whale::DirectX
{
	
	///
	/// 位图
	class WBitmapDirectX : public WBitmap
	{
	public:
		
		explicit WBitmapDirectX(WRendererDirectX *pRenderer) : m_pRenderer(pRenderer) {}
	
	public:
		
		[[nodiscard]] Bool IsGPUResourceCreated() const noexcept override;
	
	private:
		
		void OnUse() noexcept override;
		
		Bool OnGPUCreate(const WBitmapArg &arg) noexcept override;
		
		void OnGPUDestroy() noexcept override;
		
		void OnEnable() noexcept override;
		
		void OnDisable() noexcept override;
	
	private:
		
		WRendererDirectX *m_pRenderer;
		
		Microsoft::WRL::ComPtr<ID3D12Resource> m_pResource;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_pUpload;
		
		DXGI_FORMAT                        m_stTextureFormat{};
		D3D12_PLACED_SUBRESOURCE_FOOTPRINT m_stTxtLayouts{};
		
		uint32 m_width  = 0;
		uint32 m_height = 0;
		uint32 m_BPP    = 0;
		
	};
	
} // Whale
