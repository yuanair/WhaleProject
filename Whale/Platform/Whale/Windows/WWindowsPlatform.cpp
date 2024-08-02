//
// Created by admin on 2024/8/2.
//

#include "WWindowsPlatform.hpp"

#include <windows.h>
#include <ShlObj.h>

#undef GetModuleHandle

namespace Whale
{
	FString WWindowsPlatform::GetName() const
	{
		return TEXT("Windows");
	}
	
	Bool WWindowsPlatform::IsRunAsAdministrator() const
	{
		return ::IsUserAnAdmin();
	}
	
	void WWindowsPlatform::Exit(int32 result) const
	{
		::PostQuitMessage(result);
	}
	
	HModule WWindowsPlatform::GetModuleHandle() const
	{
		return {::GetModuleHandleW(nullptr)};
	}
} // Whale