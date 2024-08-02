//
// Created by admin on 2024/7/12.
//

#include "WWICForDirectX.hpp"
#include "Whale/FDebug.hpp"
#include <Whale/Windows/FCore.hpp>
#include <Whale/Windows/FFile.hpp>

namespace Whale::DirectX
{
	
	const WWICForDirectX::WICTranslate WWICForDirectX::g_WICFormats[] =
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
	
	const WWICForDirectX::WICConvert WWICForDirectX::g_WICConvert[] =
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
	
	Bool WWICForDirectX::GetTargetPixelFormat(const GUID &pSourceFormat, GUID &pTargetFormat)
	{
		//查表确定兼容的最接近格式是哪个
		pTargetFormat = pSourceFormat;
		for (auto &i: g_WICConvert)
		{
			if (::InlineIsEqualGUID(i.source, pSourceFormat))
			{
				pTargetFormat = i.target;
				return true;
			}
		}
		return false;
	}
	
	DXGI_FORMAT WWICForDirectX::GetDXGIFormatFromPixelFormat(const GUID &pPixelFormat)
	{
		//查表确定最终对应的格式是哪一个
		for (auto &g_WICFormat: g_WICFormats)
		{
			if (::InlineIsEqualGUID(g_WICFormat.wic, pPixelFormat))
			{
				return g_WICFormat.format;
			}
		}
		return DXGI_FORMAT_UNKNOWN;
	}
	
	GUID WWICForDirectX::GetPixelFormatFromDXGIFormat(const DXGI_FORMAT &pPixelFormat)
	{
		//查表确定最终对应的格式是哪一个
		for (auto &g_WICFormat: g_WICFormats)
		{
			if (g_WICFormat.format == pPixelFormat)
			{
				return g_WICFormat.wic;
			}
		}
		return GUID_WICPixelFormatUndefined;
	}
	
	void WWICForDirectX::Create()
	{
		//使用纯COM方式创建WIC类厂对象，也是调用WIC第一步要做的事情
		THROW_IF_FAILED(
			::CoCreateInstance(
				CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
				IID_PPV_ARGS(m_pIWICFactory.ReleaseAndGetAddressOf()))
		);
		
	}



//	FResult WWICForDirectX::LoadFromFile(const StringW &fileName,
//	                                     Microsoft::WRL::ComPtr<IWICBitmapSource> &pIWICSource,
//	                                     Microsoft::WRL::ComPtr<IWICPixelFormatInfo> &pIWICPixelInfo,
//	                                     DXGI_FORMAT &targetFormat)
//	{

//		Microsoft::WRL::ComPtr<IWICBitmapDecoder>     pIWICDecoder;
//		Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> pIWICFrame;
//		// 使用WIC创建并加载一个2D纹理
//
//		//使用WIC类厂对象接口加载纹理图片，并得到一个WIC解码器对象接口，图片信息就在这个接口代表的对象中了
//
//		THROW_IF_FAILED(
//			m_pIWICFactory->CreateDecoderFromFilename(
//				fileName.CStr(),              // 文件名
//				nullptr,                            // 不指定解码器，使用默认
//				GENERIC_READ,                    // 访问权限
//				WICDecodeMetadataCacheOnDemand,  // 若需要就缓冲数据
//				pIWICDecoder.ReleaseAndGetAddressOf()                    // 解码器对象
//			));
//
//		// 获取第一帧图片(因为GIF等格式文件可能会有多帧图片，其他的格式一般只有一帧图片)
//		// 实际解析出来的往往是位图格式数据
//		THROW_IF_FAILED(pIWICDecoder->GetFrame(0, pIWICFrame.ReleaseAndGetAddressOf()));
//
//		WICPixelFormatGUID wpf = {};
//		//获取WIC图片格式
//		THROW_IF_FAILED(pIWICFrame->GetPixelFormat(&wpf));
//		GUID tgFormat = {};
//
//		//通过第一道转换之后获取DXGI的等价格式
//		WWICForDirectX::GetTargetPixelFormat(wpf, tgFormat);
//		targetFormat = WWICForDirectX::GetDXGIFormatFromPixelFormat(tgFormat);
//
//
//		if (DXGI_FORMAT_UNKNOWN == targetFormat)
//		{
//			// 不支持的图片格式 目前退出了事
//			// 一般 在实际的引擎当中都会提供纹理格式转换工具，
//			// 图片都需要提前转换好，所以不会出现不支持的现象
//			FDebug::LogError(TagA, FLoadException("Unsupported image format"));
//			return E_UNEXPECTED;
//		}
//
//		if (!InlineIsEqualGUID(wpf, tgFormat))
//		{// 这个判断很重要，如果原WIC格式不是直接能转换为DXGI格式的图片时
//			// 我们需要做的就是转换图片格式为能够直接对应DXGI格式的形式
//			//创建图片格式转换器
//			Microsoft::WRL::ComPtr<IWICFormatConverter> pIConverter;
//			THROW_IF_FAILED(m_pIWICFactory->CreateFormatConverter(&pIConverter));
//
//			//初始化一个图片转换器，实际也就是将图片数据进行了格式转换
//			THROW_IF_FAILED(
//				pIConverter->Initialize(
//					pIWICFrame.Get(),                // 输入原图片数据
//					tgFormat,                         // 指定待转换的目标格式
//					WICBitmapDitherTypeNone,         // 指定位图是否有调色板，现代都是真彩位图，不用调色板，所以为None
//					nullptr,                            // 指定调色板指针
//					0.f,                             // 指定Alpha阀值
//					WICBitmapPaletteTypeCustom       // 调色板类型，实际没有使用，所以指定为Custom
//				));
//			// 调用QueryInterface方法获得对象的位图数据源接口
//			THROW_IF_FAILED(pIConverter.As(&pIWICSource));
//		}
//		else
//		{
//			//图片数据格式不需要转换，直接获取其位图数据源接口
//			THROW_IF_FAILED(pIWICFrame.As(&pIWICSource));
//		}
//
//		//获取图片像素的位大小的BPP（Bits Per Pixel）信息，用以计算图片行数据的真实大小（单位：字节）
//		Microsoft::WRL::ComPtr<IWICComponentInfo> pIWIComponentInfo;
//		THROW_IF_FAILED(m_pIWICFactory->CreateComponentInfo(
//			tgFormat, pIWIComponentInfo.GetAddressOf()));
//
//		WICComponentType type;
//		THROW_IF_FAILED(pIWIComponentInfo->GetComponentType(&type));
//
//		if (type != WICPixelFormat)
//		{
//			FDebug::LogError(TagA, FLoadException("Unknown Error"));
//			return E_UNEXPECTED;
//		}
//
//		THROW_IF_FAILED(pIWIComponentInfo.As(&pIWICPixelInfo));
//
//		return S_OK;
	//}
	
	
	FResult
	WWICForDirectX::LoadFromFile(WFile *fileHandle, Microsoft::WRL::ComPtr<IWICBitmapSource> &pIWICSource,
	                             Microsoft::WRL::ComPtr<IWICPixelFormatInfo> &pIWICPixelInfo,
	                             DXGI_FORMAT &targetFormat)
	{
		Microsoft::WRL::ComPtr<IWICBitmapDecoder>     pIWICDecoder;
		Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> pIWICFrame;
		// 使用WIC创建并加载一个2D纹理
		
		//使用WIC类厂对象接口加载纹理图片，并得到一个WIC解码器对象接口，图片信息就在这个接口代表的对象中了
		
		THROW_IF_FAILED(
			m_pIWICFactory->CreateDecoderFromFileHandle(
				reinterpret_cast<ULONG_PTR>(fileHandle->GetHandle().handle),
				nullptr,                            // 不指定解码器，使用默认
				WICDecodeMetadataCacheOnDemand,  // 若需要就缓冲数据
				pIWICDecoder.ReleaseAndGetAddressOf()                    // 解码器对象
			));
		
		// 获取第一帧图片(因为GIF等格式文件可能会有多帧图片，其他的格式一般只有一帧图片)
		// 实际解析出来的往往是位图格式数据
		THROW_IF_FAILED(pIWICDecoder->GetFrame(0, pIWICFrame.ReleaseAndGetAddressOf()));
		
		WICPixelFormatGUID wpf = {};
		//获取WIC图片格式
		THROW_IF_FAILED(pIWICFrame->GetPixelFormat(&wpf));
		GUID tgFormat = {};
		
		//通过第一道转换之后获取DXGI的等价格式
		WWICForDirectX::GetTargetPixelFormat(wpf, tgFormat);
		targetFormat = WWICForDirectX::GetDXGIFormatFromPixelFormat(tgFormat);
		
		
		if (DXGI_FORMAT_UNKNOWN == targetFormat)
		{
			// 不支持的图片格式 目前退出了事
			// 一般 在实际的引擎当中都会提供纹理格式转换工具，
			// 图片都需要提前转换好，所以不会出现不支持的现象
			FDebug::Log<CharA>(Error, TagA, "Unsupported image format");
			return E_UNEXPECTED;
		}
		
		if (!InlineIsEqualGUID(wpf, tgFormat))
		{// 这个判断很重要，如果原WIC格式不是直接能转换为DXGI格式的图片时
			// 我们需要做的就是转换图片格式为能够直接对应DXGI格式的形式
			//创建图片格式转换器
			Microsoft::WRL::ComPtr<IWICFormatConverter> pIConverter;
			THROW_IF_FAILED(m_pIWICFactory->CreateFormatConverter(&pIConverter));
			
			//初始化一个图片转换器，实际也就是将图片数据进行了格式转换
			THROW_IF_FAILED(
				pIConverter->Initialize(
					pIWICFrame.Get(),                // 输入原图片数据
					tgFormat,                         // 指定待转换的目标格式
					WICBitmapDitherTypeNone,         // 指定位图是否有调色板，现代都是真彩位图，不用调色板，所以为None
					nullptr,                            // 指定调色板指针
					0.f,                             // 指定Alpha阀值
					WICBitmapPaletteTypeCustom       // 调色板类型，实际没有使用，所以指定为Custom
				));
			// 调用QueryInterface方法获得对象的位图数据源接口
			THROW_IF_FAILED(pIConverter.As(&pIWICSource));
		}
		else
		{
			//图片数据格式不需要转换，直接获取其位图数据源接口
			THROW_IF_FAILED(pIWICFrame.As(&pIWICSource));
		}
		
		//获取图片像素的位大小的BPP（Bits Per Pixel）信息，用以计算图片行数据的真实大小（单位：字节）
		Microsoft::WRL::ComPtr<IWICComponentInfo> pIWIComponentInfo;
		THROW_IF_FAILED(m_pIWICFactory->CreateComponentInfo(
			tgFormat, pIWIComponentInfo.GetAddressOf()));
		
		WICComponentType type;
		THROW_IF_FAILED(pIWIComponentInfo->GetComponentType(&type));
		
		if (type != WICPixelFormat)
		{
			FDebug::Log<CharA>(Error, TagA, "Unknown Error");
			return E_UNEXPECTED;
		}
		
		THROW_IF_FAILED(pIWIComponentInfo.As(&pIWICPixelInfo));
		
		return S_OK;
	}
	
	Bool WWICForDirectX::IsGPUResourceCreated() const noexcept
	{
		return m_pIWICFactory;
	}
	
	void WWICForDirectX::OnResourceDestroy() noexcept
	{
		m_pIWICFactory = nullptr;
	}
	
	void WWICForDirectX::OnEnable() noexcept
	{
	
	}
	
	void WWICForDirectX::OnDisable() noexcept
	{
	
	}
	
	
}
