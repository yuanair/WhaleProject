//
// Created by admin on 2024/7/1.
//

#include "FCore.hpp"
#include "Whale/Core/FDebug.hpp"
#include "Whale/Core/WProgram.hpp"

#include <windows.h>

namespace Whale::Win32
{
	
	HInstance FCore::ShellExecuteT(HWindow hWnd, const StringA &operation, const StringA &file,
	                               const StringA &parameters,
	                               const StringA &directory, int32 showCmd)
	{
		return {
			::ShellExecuteA((HWND) hWnd.handle, operation.CStr(), file.CStr(), parameters.CStr(), directory.CStr(),
			                showCmd
			)
		};
	}
	
	
	HInstance FCore::ShellExecuteT(HWindow hWnd, const StringW &operation, const StringW &file,
	                               const StringW &parameters,
	                               const StringW &directory, int32 showCmd)
	{
		return {
			::ShellExecuteW((HWND) hWnd.handle, operation.CStr(), file.CStr(), parameters.CStr(), directory.CStr(),
			                showCmd
			)
		};
	}
	
	void FCore::Exit(int32 result)
	{
		::PostQuitMessage(result);
	}
	
	int32 FCore::GetCommandShow()
	{
		STARTUPINFOA startup_info{};
		GetStartupInfoA(&startup_info);
		
		return startup_info.dwFlags & STARTF_USESHOWWINDOW
		       ? startup_info.wShowWindow
		       : SW_SHOWDEFAULT;
	}
	
	HInstance FCore::GetInstance()
	{
		return {::GetModuleHandle(nullptr)};
	}
	
	HIcon FCore::GetIcon(int32 id)
	{
		return {::LoadImage((HINSTANCE) GetInstance().handle, MAKEINTRESOURCE(id), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR)};
	}
	
	HIcon FCore::GetIcon(int32 id, HInstance hInstance)
	{
		return {::LoadImage((HINSTANCE) hInstance.handle, MAKEINTRESOURCE(id), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR)};
	}
	
	HCursor FCore::GetCursor(int32 id)
	{
		return {
			::LoadImage((HINSTANCE) GetInstance().handle, MAKEINTRESOURCE(id), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR)
		};
	}
	
	HCursor FCore::GetCursor(int32 id, HInstance hInstance)
	{
		return {::LoadImage((HINSTANCE) hInstance.handle, MAKEINTRESOURCE(id), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR)};
	}
	
	void FCore::GainAdminPrivileges(const StringA &strApp)
	{
		SHELLEXECUTEINFOA execInfo;
		execInfo.cbSize = sizeof(execInfo);
		execInfo.lpFile = strApp.CStr();
		execInfo.cbSize = sizeof(execInfo);
		execInfo.lpVerb = "runas";
		execInfo.fMask = SEE_MASK_NO_CONSOLE;
		execInfo.nShow = SW_SHOWDEFAULT;
		
		::ShellExecuteExA(&execInfo);
	}
	
	void FCore::GainAdminPrivileges(const StringW &strApp)
	{
		SHELLEXECUTEINFOW execInfo;
		execInfo.cbSize = sizeof(execInfo);
		execInfo.lpFile = strApp.CStr();
		execInfo.cbSize = sizeof(execInfo);
		execInfo.lpVerb = L"runas";
		execInfo.fMask = SEE_MASK_NO_CONSOLE;
		execInfo.nShow = SW_SHOWDEFAULT;
		
		::ShellExecuteExW(&execInfo);
	}
	
	bool FCore::IsRunAsAdministrator()
	{
		::BOOL fIsRunAsAdmin = FALSE;
		::DWORD dwError = ERROR_SUCCESS;
		::PSID pAdministratorsGroup = nullptr;
		
		::SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
		if (!::AllocateAndInitializeSid(
			&NtAuthority,
			2,
			SECURITY_BUILTIN_DOMAIN_RID,
			DOMAIN_ALIAS_RID_ADMINS,
			0, 0, 0, 0, 0, 0,
			&pAdministratorsGroup
		))
		{
			dwError = ::GetLastError();
			goto Cleanup;
		}
		
		if (!::CheckTokenMembership(nullptr, pAdministratorsGroup, &fIsRunAsAdmin))
		{
			dwError = ::GetLastError();
			goto Cleanup;
		}

Cleanup:
		
		if (pAdministratorsGroup)
		{
			::FreeSid(pAdministratorsGroup);
			pAdministratorsGroup = nullptr;
		}
		
		if (ERROR_SUCCESS != dwError)
		{
			FDebug::LogError(TagW, MessageToStringW(HRESULT_FROM_WIN32(dwError)).CStr());
		}
		
		return fIsRunAsAdmin;
	}
	
	
	StringA FCore::GetCommandLineA()
	{
		return ::GetCommandLineA();
	}
	
	StringW FCore::GetCommandLineW()
	{
		return ::GetCommandLineW();
	}
	
	StringA FCore::MessageToStringA(HResult dwMessageId)
	{
		auto strBufferError = WHALE_NEW_CLIENT CharA[256];
		::FormatMessageA
			(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				nullptr, dwMessageId, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
				strBufferError, 256, nullptr
			);
		StringA buffer = strBufferError;
		delete[] strBufferError;
		return buffer;
	}
	
	StringW FCore::MessageToStringW(HResult dwMessageId)
	{
		auto strBufferError = WHALE_NEW_CLIENT CharW[256];
		::FormatMessageW
			(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				nullptr, dwMessageId, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
				strBufferError, 256, nullptr
			);
		StringW buffer = strBufferError;
		delete[] strBufferError;
		return buffer;
	}
	
	HResult FCore::GetLastError()
	{
		return HRESULT_FROM_WIN32(::GetLastError());
	}
	
} // Whale