//
// Created by admin on 2024/7/12.
//

#pragma once

#include "HDirectXHeader.hpp"
#include <wincodec.h>

namespace Whale
{
	
	class WHALE_API FWICForDirectX
	{
	public:
		
		static bool GetTargetPixelFormat(const GUID *pSourceFormat, GUID *pTargetFormat);
		
		static DXGI_FORMAT GetDXGIFormatFromPixelFormat(const GUID *pPixelFormat);
	
	public:
		
		///
		/// 创建WIC
		void Create();
	
	public:
		
		inline const Microsoft::WRL::ComPtr<IWICImagingFactory> &GetPIWICFactory() const { return this->pIWICFactory; }
	
	private:
		
		struct WICTranslate
		{
			GUID wic;
			DXGI_FORMAT format;
		};
		
		struct WICConvert
		{
			GUID source;
			GUID target;
		};
		
		static const WICTranslate g_WICFormats[];
		
		static const WICConvert g_WICConvert[];
	
	private:
		
		Microsoft::WRL::ComPtr<IWICImagingFactory> pIWICFactory;
		
	};
	
}
