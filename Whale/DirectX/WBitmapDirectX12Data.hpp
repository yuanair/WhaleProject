//
// Created by admin on 2024/7/12.
//

#pragma once

#include "Whale/Core/FUndefinedData.hpp"
#include "Whale/DirectX/FDirectXHeader.hpp"

#include "Whale/DirectX/FWICForDirectX.hpp"

namespace Whale
{
	class WBitmapDirectX12Data : public WObject
	{
	public:
		
		DXGI_FORMAT stTextureFormat;
		
		uint32 nWidth;
		
		uint32 nHeight;
		
		uint32 nBPP;
		
	};
}