//
// Created by admin on 2024/7/20.
//

#pragma once

#include <Windows.h>
#include <tchar.h>


// Initialize once for each new process.
// Return FALSE to fail DLL load.
int WhaleDllProcessAttach();

// Do thread-specific initialization.
int WhaleDllThreadAttach();

// Do thread-specific cleanup.
int WhaleDllThreadDetach();

// Perform any necessary cleanup.
int WhaleDllProcessDetach();

::BOOL WINAPI DllMain(
	::HINSTANCE hInstance,
	::DWORD fdwReason,
	::LPVOID lpvReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
			return ::WhaleDllProcessAttach();
		
		case DLL_THREAD_ATTACH:
			return ::WhaleDllThreadAttach();
		
		case DLL_THREAD_DETACH:
			return ::WhaleDllThreadDetach();
		
		case DLL_PROCESS_DETACH:
			
			if (lpvReserved != nullptr)
			{
				return true; // 如果程序终止，不做清理
			}
			
			return ::WhaleDllProcessDetach();
		default:
			return false;
	}
}
