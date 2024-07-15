//
// Created by admin on 2024/6/16.
//

#include "WObject.hpp"
#include <format>

namespace Whale
{
	WObject::WObject()
	{
	
	}
	
	WObject::~WObject()
	{
	
	}
	
	bool WObject::Equals(const WObject &other) const
	{
		return &other == this;
	}
	
	std::string WObject::ToString() const
	{
		return std::format("{}<{:016X}>", typeid(*this).name(), (intptr_t) this);
	}
	
	WObject *WObject::Clone() const
	{
		return new WObject;
	}
} // Whale