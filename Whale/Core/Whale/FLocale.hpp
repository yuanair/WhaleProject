//
// Created by admin on 2024/7/5.
//

#pragma once

#include "TypeDef.hpp"
#include "Whale/Container/TFString.hpp"

namespace Whale
{
	
	///
	/// 本地化
	class WHALE_API FLocale
	{
	public:

//		static StringA Between(const StringA &text, const StringA &toEncoding, const StringA &fromEncoding);
//
//		static StringW ToUTFString(const StringA &text, const StringA &fromEncoding);
//
//		static StringA UTFToString(const StringW &text, const StringA &toEncoding);
//
//		template<class StringType>
//		static StringType AToString(const StringA &text, const StringA &fromEncoding);
//
//		template<class StringType>
//		static StringType WToString(const StringW &text, const StringA &toEncoding);
//
//		inline static StringT AToTString(const StringA &text, const StringA &fromEncoding)
//		{
//			#ifdef WHALE_UNICODE
//			return ToUTFString(text, fromEncoding);
//			#else
//			return text;
//			#endif
//		}
//
//		inline static StringT WToTString(const StringW &text, const StringA &toEncoding)
//		{
//			#ifdef WHALE_UNICODE
//			return text;
//			#else
//			return UTFToString(text, toEncoding);
//			#endif
//		}
		
		///
		/// \return 是否为EOF或WEOF
		static Bool IsEOF(int32 ch);
		
		///
		/// \return 是否为空白字符
		static Bool IsSpace(int32 ch);
		
		///
		/// \return 是否为空白字符（包括0, EOF与WEOF）
		static Bool IsSpaceIncludeNull(int32 ch);
		
		///
		/// \return 是否为换行字符
		static Bool IsNewLine(int32 ch);
		
		///
		/// \return 是否为数字
		static Bool IsDigit(int32 ch);
		
		///
		/// \return 是否为大写字母
		static Bool IsUpper(int32 ch);
		
		///
		/// \return 是否为小写字母
		static Bool IsLower(int32 ch);
		
		///
		/// \return 是否为字母
		static Bool IsAlpha(int32 ch);
		
		///
		/// \return 是否为十六进制数字
		static Bool IsXDigit(int32 ch);
		
		///
		/// \return 是否为数字或字母
		static Bool IsADigit(int32 ch);
		
		///
		/// \return 是否为标点符号
		static Bool IsPunct(int32 ch);
		
		///
		/// \return 是否为控制符号
		static Bool IsCtrl(int32 ch);
		
		///
		/// 单字符转义（'n' -> '\\n'）
		/// \return 转义后的字符
		static int32 Escape(int32 ch);
		
		///
		/// 单字符反转义（'\\n' -> 'n'）
		/// \return 反转义后的字符
		static int32 Unescape(int32 ch);
		
	};

//	template<class StringType>
//	StringType FLocale::AToString(const StringA &text, const StringA &fromEncoding)
//	{
//		return text;
//	}
//
//	template<class StringType>
//	StringType FLocale::WToString(const StringW &text, const StringA &toEncoding)
//	{
//		return text;
//	}
//
//	template<>
//	inline StringA WHALE_API FLocale::AToString(const StringA &text, const StringA &fromEncoding)
//	{
//		return text;
//	}
//
//	template<>
//	inline StringW WHALE_API FLocale::AToString(const StringA &text, const StringA &fromEncoding)
//	{
//		return ToUTFString(text, fromEncoding);
//	}
//
//	template<>
//	inline StringA WHALE_API FLocale::WToString(const StringW &text, const StringA &toEncoding)
//	{
//		return UTFToString(text, toEncoding);
//	}
//
//	template<>
//	inline StringW WHALE_API FLocale::WToString(const StringW &text, const StringA &toEncoding)
//	{
//		return text;
//	}
	
} // Whale
