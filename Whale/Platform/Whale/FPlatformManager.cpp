//
// Created by admin on 2024/8/2.
//

#include "FPlatformManager.hpp"

#include "AutoPlatform.hpp"

namespace Whale
{
	FPlatformManager &FPlatformManager::Get()
	{
		static FPlatformManager platformManager;
		return platformManager;
	}
	
	WGenericPlatform *FPlatformManager::GetPlatform()
	{
		static TFUniquePtr<WGenericPlatform> platform = MakeUnique<WPlatform>();
		return platform.GetPtr();
	}
	
	WGenericLocale *FPlatformManager::GetLocale()
	{
		static TFUniquePtr<WGenericLocale> locale = MakeUnique<WLocale>();
		return locale.GetPtr();
	}
} // Whale