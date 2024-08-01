//
// Created by admin on 2024/7/20.
//

#include "FCore.hpp"

namespace Whale
{
	
	const CharA *FCore::GetAppNameA()
	{
		return "Whale";
	}
	
	const CharW *FCore::GetAppNameW()
	{
		return L"Whale";
	};
	
	const CharA *FCore::GetVersionA()
	{
		return "0.1.0-alpha";
	}
	
	const CharW *FCore::GetVersionW()
	{
		return L"0.1.0-alpha";
	}
	
	const CharA *FCore::GetBuildDataA()
	{
		return __DATE__;
	}
	
	const CharW *FCore::GetBuildDataW()
	{
		return L"" __DATE__;
	}
	
} // Whale