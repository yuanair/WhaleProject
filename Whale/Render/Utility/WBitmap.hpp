//
// Created by admin on 2024/7/12.
//

#pragma once

#include "Whale/Core/Object/WObject.hpp"

namespace Whale
{
	///
	/// 位图
	class WBitmap : public WObject
	{
	public:
		
		///
		/// 从文件加载
		/// \param fileName 文件名
		virtual void LoadFromFile(const std::wstring &fileName) = 0;
		
	};
	
} // Whale
