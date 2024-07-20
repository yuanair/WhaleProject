//
// Created by admin on 2024/7/11.
//

#pragma once

#include "Whale/Core/WObject.hpp"
#include "Whale/Core/Container/TFString.hpp"

namespace Whale
{
	///
	/// 着色器
	class WHALE_API WShader : public WObject
	{
	public:
		
		///
		/// \param fileName 文件名
		/// \returns 是否成功
		virtual bool CreateFromFile(const StringW &fileName) = 0;
		
		///
		/// 使用着色器
		virtual void Use() = 0;
		
	};
	
	
} // Whale
