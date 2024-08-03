//
// Created by admin on 2024/8/2.
//

#include "WWindowsPlatform.hpp"
#include "WWindowsFileManager.hpp"
#include "WWindowsLocale.hpp"
#include "WWindowsWindowManager.hpp"

#include <windows.h>
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
		MSG msg;
		
		program.BeginPlay();
		
		do
		{
			if (::PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessageW(&msg);
			}
			else
			{
				program.Tick();
			}
		}
		while (msg.message != WM_QUIT);
		
		program.EndPlay();
		
		return (int32) msg.wParam;
	}
	
	FString WWindowsPlatform::GetName() const
	{
		return WTEXT("Windows");
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
} // Whale