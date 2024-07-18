//
// Created by admin on 2024/7/5.
//

#include "WLocale.hpp"

#include "boost/locale.hpp"

namespace Whale
{
	StringA WLocale::Between(const StringA &text, const StringA &toEncoding, const StringA &fromEncoding)
	{
		return boost::locale::conv::between(text.CStr(), toEncoding.CStr(), fromEncoding.CStr()).c_str();
	}
	
	StringW WLocale::ToUTFString(const StringA &text, const StringA &fromEncoding)
	{
		return boost::locale::conv::to_utf<WChar>(text.CStr(), fromEncoding.CStr()).c_str();
	}
	
	StringA WLocale::UTFToString(const StringW &text, const StringA &toEncoding)
	{
		return boost::locale::conv::from_utf(text.CStr(), toEncoding.CStr()).c_str();
	}
	
	
} // Whale