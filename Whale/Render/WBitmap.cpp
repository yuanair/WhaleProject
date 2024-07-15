//
// Created by admin on 2024/7/12.
//

#include "WBitmap.hpp"

#include "Whale/DirectX/WDirectX12Data.hpp"
#include "Whale/DirectX/WBitmapDirectX12Data.hpp"
#include "WRenderer.hpp"
#include "Whale/DirectX/WRendererDirectX.hpp"

namespace Whale
{
	void WBitmapDirectX12::LoadFromFile(const std::wstring &fileName)
	{
		Microsoft::WRL::ComPtr<IWICBitmapDecoder> pIWICDecoder;
		Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> pIWICFrame;
		auto &renderer = WRenderer::GetRenderer<WRendererDirectX>();
		// 使用WIC创建并加载一个2D纹理
		
		//使用WIC类厂对象接口加载纹理图片，并得到一个WIC解码器对象接口，图片信息就在这个接口代表的对象中了
		
		THROW_IF_FAILED(
			renderer.GetData()->wicForDirectX.GetPIWICFactory()->CreateDecoderFromFilename(
				fileName.c_str(),              // 文件名
				nullptr,                            // 不指定解码器，使用默认
				GENERIC_READ,                    // 访问权限
				WICDecodeMetadataCacheOnDemand,  // 若需要就缓冲数据
				&pIWICDecoder                    // 解码器对象
			));
		
		// 获取第一帧图片(因为GIF等格式文件可能会有多帧图片，其他的格式一般只有一帧图片)
		// 实际解析出来的往往是位图格式数据
		THROW_IF_FAILED(pIWICDecoder->GetFrame(0, &pIWICFrame));
		
		WICPixelFormatGUID wpf = {};
		//获取WIC图片格式
		THROW_IF_FAILED(pIWICFrame->GetPixelFormat(&wpf));
		GUID tgFormat = {};
		
		//通过第一道转换之后获取DXGI的等价格式
		if (FWICForDirectX::GetTargetPixelFormat(&wpf, &tgFormat))
		{
			data->stTextureFormat = FWICForDirectX::GetDXGIFormatFromPixelFormat(&tgFormat);
		}
		
		if (DXGI_FORMAT_UNKNOWN == data->stTextureFormat)
		{
			// 不支持的图片格式 目前退出了事
			// 一般 在实际的引擎当中都会提供纹理格式转换工具，
			// 图片都需要提前转换好，所以不会出现不支持的现象
			FDebug::Fatal(L"Unsupported image format");
			throw;
		}
		
		// 定义一个位图格式的图片数据对象接口
		Microsoft::WRL::ComPtr<IWICBitmapSource> pIBMP;
		
		if (!InlineIsEqualGUID(wpf, tgFormat))
		{// 这个判断很重要，如果原WIC格式不是直接能转换为DXGI格式的图片时
			// 我们需要做的就是转换图片格式为能够直接对应DXGI格式的形式
			//创建图片格式转换器
			Microsoft::WRL::ComPtr<IWICFormatConverter> pIConverter;
			THROW_IF_FAILED(renderer.GetData()->wicForDirectX.GetPIWICFactory()->CreateFormatConverter(&pIConverter));
			
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
			THROW_IF_FAILED(pIConverter.As(&pIBMP));
		}
		else
		{
			//图片数据格式不需要转换，直接获取其位图数据源接口
			THROW_IF_FAILED(pIWICFrame.As(&pIBMP));
		}
		//获得图片大小（单位：像素）
		THROW_IF_FAILED(pIBMP->GetSize(&data->nWidth, &data->nHeight));
		
		//获取图片像素的位大小的BPP（Bits Per Pixel）信息，用以计算图片行数据的真实大小（单位：字节）
		Microsoft::WRL::ComPtr<IWICComponentInfo> pIWIComponentInfo;
		THROW_IF_FAILED(renderer.GetData()->wicForDirectX.GetPIWICFactory()->CreateComponentInfo(
			tgFormat, pIWIComponentInfo.GetAddressOf()));
		
		WICComponentType type;
		THROW_IF_FAILED(pIWIComponentInfo->GetComponentType(&type));
		
		if (type != WICPixelFormat)
		{
			FDebug::Fatal(L"Error");
			throw;
		}
		
		Microsoft::WRL::ComPtr<IWICPixelFormatInfo> pIWICPixelInfo;
		THROW_IF_FAILED(pIWIComponentInfo.As(&pIWICPixelInfo));
		
		// 到这里终于可以得到BPP了，这也是我看的比较吐血的地方，为了BPP居然饶了这么多环节
		THROW_IF_FAILED(pIWICPixelInfo->GetBitsPerPixel(&data->nBPP));
		
		// 计算图片实际的行大小（单位：字节），这里使用了一个上取整除法即（A+B-1）/B ，
		// 这曾经被传说是微软的面试题,希望你已经对它了如指掌
		uint32 nPicRowPitch = (uint64_t(data->nWidth) * uint64_t(data->nBPP) + 7u) / 8u;
	}
} // Whale