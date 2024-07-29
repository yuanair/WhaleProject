//
// Created by admin on 2024/7/12.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"
#include "Whale/Core/Container/TFString.hpp"
#include "TIGPUResource.hpp"
#include "WImage.hpp"

#include "dxgiformat.h"

namespace Whale
{
	
	
	///
	/// 位图参数
	struct WBitmapArg
	{
		
		/// 文件名
		StringW     m_fileName;
		/// 格式
		DXGI_FORMAT m_format = DXGI_FORMAT_R8G8B8A8_UNORM;
		
	};
	
	///
	/// 位图
	class WHALE_API WBitmap : public WImage, public TIGPUResource<const WBitmapArg, Bool>
	{
	public:
		
		void Use() noexcept { if (this->IsEnabled()) OnUse(); }
	
	private:
		
		virtual void OnUse() noexcept = 0;
		
	};
	
} // Whale
