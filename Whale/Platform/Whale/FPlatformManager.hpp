//
// Created by admin on 2024/8/2.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include "WGenericPlatform.hpp"
#include "WGenericLocale.hpp"

namespace Whale
{
	
	/// 平台管理器
	class WHALE_API FPlatformManager
	{
	public:
		
		static FPlatformManager &Get();
	
	public:
		
		/// 获取当前平台
		WGenericPlatform *GetPlatform();
		
		/// 获取本地化类
		WGenericLocale *GetLocale();
		
	};
	
} // Whale
