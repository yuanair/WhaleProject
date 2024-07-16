//
// Created by admin on 2024/7/11.
//

#pragma once

#include "Whale/Core/Object/WObject.hpp"

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
		virtual bool CreateFromFile(const std::wstring &fileName) = 0;
		
		///
		/// 使用着色器
		virtual void Use() = 0;
		
	};
	
	
} // Whale
