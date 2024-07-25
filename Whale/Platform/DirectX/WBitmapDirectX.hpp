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
		
		void LoadFromFile(const StringW &fileName) override;
	
	private:
		
		void OnEnable() noexcept override;
		
		void OnDisable() noexcept override;
	
	private:
		
		WRendererDirectX *m_pRenderer;
		
		Microsoft::WRL::ComPtr<ID3D12Resource> m_pResource;
		
		DXGI_FORMAT m_stTextureFormat{};
		
		uint32 m_width = 0;
		
		uint32 m_height = 0;
		
		uint32 m_BPP = 0;
		
	};
	
} // Whale
