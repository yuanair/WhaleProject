//
// Created by admin on 2024/7/15.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"

namespace Whale
{
	
	///
	/// c string
	class WHALE_API FCString
	{
	public:
		
		///
		/// \param str 字符串
		/// \return 字符串长度（包括结束符null）
		template<typename ElemT>
		static SizeT Length(const ElemT *str);
		
		///
		/// \param str 字符串
		/// \return 字符串长度（不包括结束符no null）
		template<typename ElemT>
		static SizeT LengthNoNull(const ElemT *str);
		
		
	};
	
	template<typename ElemT>
	SizeT FCString::Length(const ElemT *str)
	{
		if (str == nullptr) return 0;
		SizeT index = 0;
		while (str[index] != 0)
		{
			++index;
		}
		++index;
		return index;
	}
	
	template<typename ElemT>
	SizeT FCString::LengthNoNull(const ElemT *str)
	{
		if (str == nullptr) return 0;
		SizeT index = 0;
		while (str[index] != 0)
		{
			++index;
		}
		return index;
	}
	
} // Whale
