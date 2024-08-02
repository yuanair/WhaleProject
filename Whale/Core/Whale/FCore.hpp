//
// Created by admin on 2024/7/20.
//

#pragma once

#include "TypeDef.hpp"

namespace Whale
{
	
	class WHALE_API FCore
	{
	public:
		
		static const Char *GetAppName();
		
		static const CharA *GetAppNameA();
		
		static const CharW *GetAppNameW();
		
		static const Char *GetVersion();
		
		static const CharA *GetVersionA();
		
		static const CharW *GetVersionW();
		
		static const Char *GetBuildData();
		
		static const CharA *GetBuildDataA();
		
		static const CharW *GetBuildDataW();
	};
	
} // Whale
