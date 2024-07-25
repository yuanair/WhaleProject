//
// Created by admin on 2024/7/25.
//

#pragma once

#include "Whale/Core/WObject.hpp"
#include "Whale/Tool/IEnable.hpp"

namespace Whale
{
	///
	/// 图片
	class WHALE_API WImage : public WObject, public Tool::IEnable
	{
	public:
		
		///
		/// 从文件加载
		/// \param fileName 文件名
		virtual void LoadFromFile(const StringW &fileName) = 0;
		
	};
	
} // Whale
