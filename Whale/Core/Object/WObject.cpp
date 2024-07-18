//
// Created by admin on 2024/6/16.
//

#include "WObject.hpp"

namespace Whale
{
	WObject::WObject() = default;
	
	WObject::~WObject() = default;

//	void WObject::ToString(StringA &target) const
//	{
//		target = std::format("{}<{:016X}>", typeid(*this).name(), (intptr_t) this).c_str();
//	}
//
//	void WObject::ToString(StringW &target) const
//	{
//		target = std::format(
//			L"{}<{:016X}>", WLocale::ToUTFString(typeid(*this).name(), "UTF-8").CStr(), (intptr_t) this
//		).c_str();
//	}
	
} // Whale