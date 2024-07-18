//
// Created by admin on 2024/7/15.
//

#pragma once

#include "HTypeDef.hpp"

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
		template<typename CharT>
		static SizeT Length(const CharT *str);
		
		///
		/// \param str 字符串
		/// \return 字符串长度（不包括结束符no null）
		template<typename CharT>
		static SizeT LengthNoNull(const CharT *str);
		
		
	};
	
	template<typename CharT>
	SizeT FCString::Length(const CharT *str)
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
	
	template<typename CharT>
	SizeT FCString::LengthNoNull(const CharT *str)
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
