//
// Created by admin on 2024/7/12.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/Container/TFString.hpp>
#include "TIGPUResource.hpp"
#include "WImage.hpp"

#include <dxgiformat.h>
#include <Eigen/Core>

namespace Whale
{
	
	
	///
	/// 位图参数
	struct WBitmapArg
	{
		
		/// 文件名
		StringW m_fileName;
		/// 垂直翻转（速度影响比较小，仅改变数据拷贝顺序）
		Bool    m_flipVertical = true;
		
	};
	
	///
	/// 位图
	class WHALE_API WBitmap : public WImage, public TIGPUResource
	{
	public:
		
		/// 从文件创建
		virtual Bool CreateFromFile(const WBitmapArg &arg) = 0;
		
		/// 宽度
		virtual uint64 GetWidth() noexcept = 0;
		
		/// 高度
		virtual uint32 GetHeight() noexcept = 0;
		
		void Use() noexcept { if (this->IsEnabled()) OnUse(); }
	
	private:
		
		virtual void OnUse() noexcept = 0;
		
	};
	
} // Whale
