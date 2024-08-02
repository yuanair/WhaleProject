//
// Created by admin on 2024/8/2.
//

#include "WGenericFileManager.hpp"

#include "AutoPlatform.hpp"

namespace Whale
{
	
	WGenericFileManager &WGenericFileManager::Get()
	{
		static WFileManager fileManager;
		return fileManager;
	}
} // Whale