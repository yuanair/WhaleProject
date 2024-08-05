//
// Created by admin on 2024/8/2.
//

#include "WWindowsPlatform.hpp"
#include "WWindowsFileManager.hpp"
#include "WWindowsLocale.hpp"
#include "WWindowsTime.hpp"
#include "WWindowsTimer.hpp"
#include "WWindowsWindowManager.hpp"
#include "../WProgram.hpp"

#include <windows.h>
#include <lm.h>
#include <ShlObj.h>

#undef GetModuleHandle

namespace Whale
{
	WWindowsPlatform &WWindowsPlatform::Get()
	{
		static WWindowsPlatform platform;
		return platform;
	}
	
	int32 WWindowsPlatform::Run(WProgram &program) const
	{
		program.BeginPlay();
		
		do
		{
			program.Tick();
			Sleep(100);
		}
		while (!IsCalledExit());
		
		program.EndPlay();
		
		return 0;
	}
	
	FString WWindowsPlatform::GetName() const
	{
		return WTEXT("Windows");
	}
	
	FString WWindowsPlatform::GetVersion() const
	{
		WKSTA_INFO_102 *buffer = nullptr;
		::NetWkstaGetInfo(nullptr, 102, reinterpret_cast<LPBYTE *>(&buffer));
		if (buffer == nullptr) return WTEXT("nullptr");
		FString result;
		result += GetLocale().ToFString(static_cast<uint32>(buffer->wki102_ver_major));
		result += WTEXT(".");
		result += GetLocale().ToFString(static_cast<uint32>(buffer->wki102_ver_minor));
		::NetApiBufferFree(buffer);
		return result;
//		if (::IsWindows10OrGreater()) return WTEXT("10");
//		if (::IsWindows8Point1OrGreater()) return WTEXT("8.1");
//		if (::IsWindows8OrGreater()) return WTEXT("8");
//		if (::IsWindows7SP1OrGreater()) return WTEXT("7 Service Pack 1");
//		if (::IsWindows7OrGreater()) return WTEXT("7");
//		if (::IsWindowsVistaSP2OrGreater()) return WTEXT("Vista Service Pack 2");
//		if (::IsWindowsVistaSP1OrGreater()) return WTEXT("Vista Service Pack 1");
//		if (::IsWindowsVistaOrGreater()) return WTEXT("Vista");
//		if (::IsWindowsXPSP3OrGreater()) return WTEXT("XP Service Pack 3");
//		if (::IsWindowsXPSP2OrGreater()) return WTEXT("XP Service Pack 2");
//		if (::IsWindowsXPSP1OrGreater()) return WTEXT("XP Service Pack 1");
//		if (::IsWindowsXPOrGreater()) return WTEXT("XP");
//		return WTEXT("Unknown");
	}
	
	FString WWindowsPlatform::GetNewLine() const
	{
		return WTEXT("\r\n");
	}
	
	Bool WWindowsPlatform::IsRunAsAdministrator() const
	{
		return ::IsUserAnAdmin();
	}
	
	void WWindowsPlatform::Exit(int32 result) const
	{
		m_isCalledExit = true;
		::PostQuitMessage(result);
	}
	
	HModule WWindowsPlatform::GetModuleHandle() const
	{
		return {::GetModuleHandleW(nullptr)};
	}
	
	WGenericFileManager &WWindowsPlatform::GetFileManager() const
	{
		return WWindowsFileManager::Get();
	}
	
	WGenericLocale &WWindowsPlatform::GetLocale() const
	{
		return WWindowsLocale::Get();
	}
	
	WGenericWindowManager &WWindowsPlatform::GetWindowManager() const
	{
		return WWindowsWindowManager::Get();
	}
	
	WGenericTime &WWindowsPlatform::GetTime() const
	{
		return WWindowsTime::Get();
	}
	
	WGenericTimer *WWindowsPlatform::NewTimer() const
	{
		return WHALE_NEW_CLIENT WWindowsTimer();
	}
	
	WWindowsPlatform::WWindowsPlatform()
		: m_isCalledExit(false)
	{
	
	}
} // Whale