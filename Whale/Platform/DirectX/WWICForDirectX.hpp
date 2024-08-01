//
// Created by admin on 2024/7/12.
//

#pragma once

#include "HDirectXHeader.hpp"
#include "Whale/Core/WObject.hpp"
#include "Whale/Platform/TIGPUResource.hpp"
#include <wincodec.h>

#pragma comment(lib, "WindowsCodecs.lib")

namespace Whale::DirectX
{
	
	/// WIC
	class WHALE_API WWICForDirectX : public WObject, public TIGPUResource
	{
	public:
		
		static Bool GetTargetPixelFormat(const GUID &pSourceFormat, GUID &pTargetFormat);
		
		static DXGI_FORMAT GetDXGIFormatFromPixelFormat(const GUID &pPixelFormat);
		
		static GUID GetPixelFormatFromDXGIFormat(const DXGI_FORMAT &pPixelFormat);
	
	public:
		
		///
		/// 创建WIC
		void Create();
		
		/// 从文件加载图片
		/// \param fileName 文件名
		/// \param targetFormat 目标格式
		Win32::FResult LoadFromFile(const StringA &fileName,
		                            Microsoft::WRL::ComPtr<IWICBitmapSource> &pIWICSource,
		                            Microsoft::WRL::ComPtr<IWICPixelFormatInfo> &pIWICPixelInfo,
		                            DXGI_FORMAT &targetFormat);
		
		/// 从文件加载图片
		/// \param fileName 文件名
		/// \param targetFormat 目标格式
		Win32::FResult LoadFromFile(const StringW &fileName,
		                            Microsoft::WRL::ComPtr<IWICBitmapSource> &pIWICSource,
		                            Microsoft::WRL::ComPtr<IWICPixelFormatInfo> &pIWICPixelInfo,
		                            DXGI_FORMAT &targetFormat);
		
		/// 从文件句柄加载图片
		/// \param fileHandle 文件
		/// \param targetFormat 目标格式
		Win32::FResult LoadFromFile(Win32::HHandle fileHandle,
		                            Microsoft::WRL::ComPtr<IWICBitmapSource> &pIWICSource,
		                            Microsoft::WRL::ComPtr<IWICPixelFormatInfo> &pIWICPixelInfo,
		                            DXGI_FORMAT &targetFormat);
	
	public:
		
		[[nodiscard]] Bool IsGPUResourceCreated() const noexcept override;
	
	private:
		
		void OnResourceDestroy() noexcept override;
		
		void OnEnable() noexcept override;
		
		void OnDisable() noexcept override;
	
	private:
		
		struct WICTranslate
		{
			GUID        wic;
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
		
		Microsoft::WRL::ComPtr<IWICImagingFactory> m_pIWICFactory;
		
	};
	
}
