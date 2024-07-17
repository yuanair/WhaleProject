//
// Created by admin on 2024/7/5.
//

#include "WLocale.hpp"

#include "boost/locale.hpp"

namespace Whale
{
	FTStringA WLocale::Between(const FTStringA &text, const FTStringA &toEncoding, const FTStringA &fromEncoding)
	{
		return boost::locale::conv::between(text.CStr(), toEncoding.CStr(), fromEncoding.CStr()).c_str();
	}
	
	FTStringW WLocale::ToUTFString(const FTStringA &text, const FTStringA &fromEncoding)
	{
		return boost::locale::conv::to_utf<WChar>(text.CStr(), fromEncoding.CStr()).c_str();
	}
	
	FTStringA WLocale::UTFToString(const FTStringW &text, const FTStringA &toEncoding)
	{
		return boost::locale::conv::from_utf(text.CStr(), toEncoding.CStr()).c_str();
	}
	
	
} // Whale