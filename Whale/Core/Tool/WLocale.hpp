//
// Created by admin on 2024/7/5.
//

#pragma once

#include "Whale/Core/Tool/HTypeDef.hpp"
#include "Whale/Core/Object/WObject.hpp"
#include "Whale/Core/Container/TFString.hpp"

namespace Whale
{
	
	///
	/// 本地化
	class WHALE_API WLocale : public WObject
	{
	public:
		
		static StringA Between(const StringA &text, const StringA &toEncoding, const StringA &fromEncoding);
		
		static StringW ToUTFString(const StringA &text, const StringA &fromEncoding);
		
		static StringA UTFToString(const StringW &text, const StringA &toEncoding);
		
		inline static StringT AToTString(const StringA &text, const StringA &fromEncoding)
		{
			#ifdef WHALE_UNICODE
			return ToUTFString(text, fromEncoding);
			#else
			return text;
			#endif
		}
		
		inline static StringT WToTString(const StringW &text, const StringA &toEncoding)
		{
			#ifdef WHALE_UNICODE
			return text
			#else
			return UTFToString(text, toEncoding);
			#endif
		}
		
	};
	
} // Whale
