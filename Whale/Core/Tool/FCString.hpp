//
// Created by admin on 2024/7/15.
//

#pragma once

#include "FTypeDef.hpp"

namespace Whale
{
	
	///
	/// c string
	template<class CharT>
	class WHALE_API FCString
	{
	public:
		
		///
		/// \param str 字符串
		/// \return 字符串长度（包括结束符null）
		static SizeT Length(const CharT *str);
		
		///
		/// \param str 字符串
		/// \return 字符串长度（不包括结束符no null）
		static SizeT LengthNoNull(const CharT *str);
		
	};
	
	template<class CharT>
	SizeT FCString<CharT>::Length(const CharT *str)
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
	
	template<class CharT>
	SizeT FCString<CharT>::LengthNoNull(const CharT *str)
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
