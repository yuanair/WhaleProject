//
// Created by admin on 2024/8/2.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>

namespace Whale
{
	
	/// 本地化管理器
	class WHALE_API WGenericLocale : public WObject
	{
	public:
		
		WGenericLocale() = default;
		
		WGenericLocale(const WGenericLocale &) = delete;
	
	public:
		
		WGenericLocale &operator=(const WGenericLocale &) = delete;
	
	public:
	
	
	};
	
} // Whale
