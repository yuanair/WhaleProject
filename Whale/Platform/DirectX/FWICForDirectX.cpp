//
// Created by admin on 2024/7/12.
//

#include "FWICForDirectX.hpp"

namespace Whale::DirectX
{
	
	const FWICForDirectX::WICTranslate FWICForDirectX::g_WICFormats[] =
		{//WIC格式与DXGI像素格式的对应表，该表中的格式为被支持的格式
			{GUID_WICPixelFormat128bppRGBAFloat,    DXGI_FORMAT_R32G32B32A32_FLOAT},
			
			{GUID_WICPixelFormat64bppRGBAHalf,      DXGI_FORMAT_R16G16B16A16_FLOAT},
			{GUID_WICPixelFormat64bppRGBA,          DXGI_FORMAT_R16G16B16A16_UNORM},
			
			{GUID_WICPixelFormat32bppRGBA,          DXGI_FORMAT_R8G8B8A8_UNORM},
			{GUID_WICPixelFormat32bppBGRA,          DXGI_FORMAT_B8G8R8A8_UNORM}, // DXGI 1.1
			{GUID_WICPixelFormat32bppBGR,           DXGI_FORMAT_B8G8R8X8_UNORM}, // DXGI 1.1
			
			{GUID_WICPixelFormat32bppRGBA1010102XR, DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM}, // DXGI 1.1
			{GUID_WICPixelFormat32bppRGBA1010102,   DXGI_FORMAT_R10G10B10A2_UNORM},
			
			{GUID_WICPixelFormat16bppBGRA5551,      DXGI_FORMAT_B5G5R5A1_UNORM},
			{GUID_WICPixelFormat16bppBGR565,        DXGI_FORMAT_B5G6R5_UNORM},
			
			{GUID_WICPixelFormat32bppGrayFloat,     DXGI_FORMAT_R32_FLOAT},
			{GUID_WICPixelFormat16bppGrayHalf,      DXGI_FORMAT_R16_FLOAT},
			{GUID_WICPixelFormat16bppGray,          DXGI_FORMAT_R16_UNORM},
			{GUID_WICPixelFormat8bppGray,           DXGI_FORMAT_R8_UNORM},
			
			{GUID_WICPixelFormat8bppAlpha,          DXGI_FORMAT_A8_UNORM},
		};
	
	const FWICForDirectX::WICConvert FWICForDirectX::g_WICConvert[] =
		{
			// 目标格式一定是最接近的被支持的格式
			{GUID_WICPixelFormatBlackWhite,           GUID_WICPixelFormat8bppGray}, // DXGI_FORMAT_R8_UNORM
			
			{GUID_WICPixelFormat1bppIndexed,          GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
			{GUID_WICPixelFormat2bppIndexed,          GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
			{GUID_WICPixelFormat4bppIndexed,          GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
			{GUID_WICPixelFormat8bppIndexed,          GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
			
			{GUID_WICPixelFormat2bppGray,             GUID_WICPixelFormat8bppGray}, // DXGI_FORMAT_R8_UNORM
			{GUID_WICPixelFormat4bppGray,             GUID_WICPixelFormat8bppGray}, // DXGI_FORMAT_R8_UNORM
			
			{GUID_WICPixelFormat16bppGrayFixedPoint,  GUID_WICPixelFormat16bppGrayHalf}, // DXGI_FORMAT_R16_FLOAT
			{GUID_WICPixelFormat32bppGrayFixedPoint,  GUID_WICPixelFormat32bppGrayFloat}, // DXGI_FORMAT_R32_FLOAT
			
			{GUID_WICPixelFormat16bppBGR555,          GUID_WICPixelFormat16bppBGRA5551}, // DXGI_FORMAT_B5G5R5A1_UNORM
			
			{GUID_WICPixelFormat32bppBGR101010,       GUID_WICPixelFormat32bppRGBA1010102}, // DXGI_FORMAT_R10G10B10A2_UNORM
			
			{GUID_WICPixelFormat24bppBGR,             GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
			{GUID_WICPixelFormat24bppRGB,             GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
			{GUID_WICPixelFormat32bppPBGRA,           GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
			{GUID_WICPixelFormat32bppPRGBA,           GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
			
			{GUID_WICPixelFormat48bppRGB,             GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
			{GUID_WICPixelFormat48bppBGR,             GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
			{GUID_WICPixelFormat64bppBGRA,            GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
			{GUID_WICPixelFormat64bppPRGBA,           GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
			{GUID_WICPixelFormat64bppPBGRA,           GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
			
			{GUID_WICPixelFormat48bppRGBFixedPoint,   GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT
			{GUID_WICPixelFormat48bppBGRFixedPoint,   GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT
			{GUID_WICPixelFormat64bppRGBAFixedPoint,  GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT
			{GUID_WICPixelFormat64bppBGRAFixedPoint,  GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT
			{GUID_WICPixelFormat64bppRGBFixedPoint,   GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT
			{GUID_WICPixelFormat48bppRGBHalf,         GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT
			{GUID_WICPixelFormat64bppRGBHalf,         GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT
			
			{GUID_WICPixelFormat128bppPRGBAFloat,     GUID_WICPixelFormat128bppRGBAFloat}, // DXGI_FORMAT_R32G32B32A32_FLOAT
			{GUID_WICPixelFormat128bppRGBFloat,       GUID_WICPixelFormat128bppRGBAFloat}, // DXGI_FORMAT_R32G32B32A32_FLOAT
			{GUID_WICPixelFormat128bppRGBAFixedPoint, GUID_WICPixelFormat128bppRGBAFloat}, // DXGI_FORMAT_R32G32B32A32_FLOAT
			{GUID_WICPixelFormat128bppRGBFixedPoint,  GUID_WICPixelFormat128bppRGBAFloat}, // DXGI_FORMAT_R32G32B32A32_FLOAT
			{GUID_WICPixelFormat32bppRGBE,            GUID_WICPixelFormat128bppRGBAFloat}, // DXGI_FORMAT_R32G32B32A32_FLOAT
			
			{GUID_WICPixelFormat32bppCMYK,            GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
			{GUID_WICPixelFormat64bppCMYK,            GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
			{GUID_WICPixelFormat40bppCMYKAlpha,       GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
			{GUID_WICPixelFormat80bppCMYKAlpha,       GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
			
			{GUID_WICPixelFormat32bppRGB,             GUID_WICPixelFormat32bppRGBA}, // DXGI_FORMAT_R8G8B8A8_UNORM
			{GUID_WICPixelFormat64bppRGB,             GUID_WICPixelFormat64bppRGBA}, // DXGI_FORMAT_R16G16B16A16_UNORM
			{GUID_WICPixelFormat64bppPRGBAHalf,       GUID_WICPixelFormat64bppRGBAHalf}, // DXGI_FORMAT_R16G16B16A16_FLOAT
		};
	
	bool FWICForDirectX::GetTargetPixelFormat(const GUID *pSourceFormat, GUID *pTargetFormat)
	{
		//查表确定兼容的最接近格式是哪个
		*pTargetFormat = *pSourceFormat;
		for (auto &i: g_WICConvert)
		{
			if (::InlineIsEqualGUID(i.source, *pSourceFormat))
			{
				*pTargetFormat = i.target;
				return true;
			}
		}
		return false;
	}
	
	DXGI_FORMAT FWICForDirectX::GetDXGIFormatFromPixelFormat(const GUID *pPixelFormat)
	{
		//查表确定最终对应的DXGI格式是哪一个
		for (auto &g_WICFormat: g_WICFormats)
		{
			if (::InlineIsEqualGUID(g_WICFormat.wic, *pPixelFormat))
			{
				return g_WICFormat.format;
			}
		}
		return DXGI_FORMAT_UNKNOWN;
	}
	
	void FWICForDirectX::Create()
	{
		//使用纯COM方式创建WIC类厂对象，也是调用WIC第一步要做的事情
		THROW_IF_FAILED(
			::CoCreateInstance(
				CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
				IID_PPV_ARGS(&pIWICFactory))
		);
		
	}
	
}
