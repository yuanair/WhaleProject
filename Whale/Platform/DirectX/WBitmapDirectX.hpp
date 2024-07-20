//
// Created by admin on 2024/7/16.
//

#pragma once

#include "Whale/Platform/WBitmap.hpp"
#include "HDirectXHeader.hpp"

namespace Whale::DirectX
{
	
	///
	/// 位图
	class WBitmapDirectX : public WBitmap
	{
	public:
		
		void LoadFromFile(const std::wstring &fileName) override;
	
	private:
		
		DXGI_FORMAT stTextureFormat;
		
		uint32 nWidth;
		
		uint32 nHeight;
		
		uint32 nBPP;
		
	};
	
} // Whale
