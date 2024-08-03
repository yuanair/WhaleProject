//
// Created by admin on 2024/8/2.
//

#include "FPlatformManager.hpp"

#ifdef WHALE_TARGET_WINDOWS
	
	#include "Windows/WWindowsPlatform.hpp"

#endif

namespace Whale
{
	FPlatformManager &FPlatformManager::Get()
	{
		static FPlatformManager platformManager;
		return platformManager;
	}
	
	WGenericPlatform &FPlatformManager::GetPlatform()
	{
		return WPlatform::Get();
	}
	
	WGenericLocale &FPlatformManager::GetLocale()
	{
		return GetPlatform().GetLocale();
	}
	
	WGenericFileManager &FPlatformManager::GetFileManager()
	{
		return GetPlatform().GetFileManager();
	}
} // Whale