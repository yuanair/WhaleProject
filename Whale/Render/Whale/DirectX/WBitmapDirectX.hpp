//
// Created by admin on 2024/7/16.
//

#pragma once

#include <Whale/WBitmap.hpp>
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
		
		Bool CreateFromFile(const WBitmapArg &arg) override;
		
		uint64 GetWidth() noexcept override;
		
		uint32 GetHeight() noexcept override;
		
		[[nodiscard]] Bool IsGPUResourceCreated() const noexcept override;
	
	private:
		
		void OnResourceDestroy() noexcept override;
		
		void OnUse() noexcept override;
		
		void OnEnable() noexcept override;
		
		void OnDisable() noexcept override;
	
	private:
		
		WRendererDirectX *m_pRenderer;
		
		Microsoft::WRL::ComPtr<ID3D12Resource> m_pResource;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_pUpload;
		
		DXGI_FORMAT                        m_stTextureFormat{};
		D3D12_PLACED_SUBRESOURCE_FOOTPRINT m_stTxtLayouts{};
		
	};
	
} // Whale
