//
// Created by admin on 2024/7/16.
//

#pragma once

#include "Whale/Render/Utility/WBitmap.hpp"
#include "Whale/Render/DirectX/HDirectXHeader.hpp"

namespace Whale
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
