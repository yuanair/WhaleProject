//
// Created by admin on 2024/7/5.
//

#include "WLocale.hpp"

#include <boost/locale.hpp>

namespace Whale
{
	std::string
	WLocale::Between(const std::string &text, const std::string &to_encoding, const std::string &from_encoding)
	{
		return boost::locale::conv::between(text, to_encoding, from_encoding);
	}
	
	std::wstring WLocale::ToUTFString(const std::string &text, const std::string &from_encoding)
	{
		return boost::locale::conv::to_utf<WChar>(text, from_encoding);
	}
	
	std::string
	WLocale::UTFToString(const std::wstring &text, const std::string &to_encoding)
	{
		return boost::locale::conv::from_utf(text, to_encoding);
	}
	
	
} // Whale