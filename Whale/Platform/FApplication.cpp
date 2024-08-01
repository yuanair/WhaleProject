//
// Created by admin on 2024/8/1.
//

#include "FApplication.hpp"
#include "Whale/Platform/Win32/FCore.hpp"

namespace Whale
{
	void FApplication::Exit(int32 result) noexcept
	{
		#if WHALE_TARGET == WHALE_TARGET_WINDOWS
		Win32::FCore::Exit(result);
		#else
		throw;
		#endif
	}
	
	Bool FApplication::IsRunAsAdministrator() noexcept
	{
		#if WHALE_TARGET == WHALE_TARGET_WINDOWS
		return Win32::FCore::IsRunAsAdministrator();
		#else
		throw;
		#endif
	}
} // Whale