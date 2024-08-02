//
// Created by admin on 2024/7/1.
//

#include "FCore.hpp"

#include <windows.h>
#include <ShlObj.h>

namespace Whale::Windows
{
	
	template<>
	WHALE_API HInstance FCore::ShellExecuteT<CharA>(HWindow hWindow, const StringA &operation, const StringA &file,
	                                                const StringA &parameters,
	                                                const StringA &directory, int32 showCmd)
	{
		return {
			::ShellExecuteA((HWND) hWindow.handle, operation.CStr(), file.CStr(), parameters.CStr(), directory.CStr(),
			                showCmd
			)
		};
	}
	
	template<>
	WHALE_API HInstance FCore::ShellExecuteT<CharW>(HWindow hWindow, const StringW &operation, const StringW &file,
	                                                const StringW &parameters,
	                                                const StringW &directory, int32 showCmd)
	{
		return {
			::ShellExecuteW((HWND) hWindow.handle, operation.CStr(), file.CStr(), parameters.CStr(), directory.CStr(),
			                showCmd
			)
		};
	}
	
	void FCore::Exit(int32 result)
	{
		::PostQuitMessage(result);
	}
	
	template<>
	WHALE_API int32 FCore::GetCommandShow<CharA>()
	{
		STARTUPINFOA startup_info{};
		GetStartupInfoA(&startup_info);
		
		return startup_info.dwFlags & STARTF_USESHOWWINDOW
		       ? startup_info.wShowWindow
		       : SW_SHOWDEFAULT;
	}
	
	template<>
	WHALE_API int32 FCore::GetCommandShow<CharW>()
	{
		STARTUPINFOW startup_info{};
		GetStartupInfoW(&startup_info);
		
		return startup_info.dwFlags & STARTF_USESHOWWINDOW
		       ? startup_info.wShowWindow
		       : SW_SHOWDEFAULT;
	}
	
	template<>
	WHALE_API HInstance FCore::GetInstance<CharA>()
	{
		return {::GetModuleHandleA(nullptr)};
	}
	
	template<>
	WHALE_API HInstance FCore::GetInstance<CharW>()
	{
		return {::GetModuleHandleW(nullptr)};
	}
	
	template<>
	WHALE_API HIcon FCore::GetIcon<CharA>(int32 id, HInstance hInstance)
	{
		return {::LoadImageA((HINSTANCE) hInstance.handle, MAKEINTRESOURCEA(id), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR)};
	}
	
	template<>
	WHALE_API HIcon FCore::GetIcon<CharW>(int32 id, HInstance hInstance)
	{
		return {::LoadImageW((HINSTANCE) hInstance.handle, MAKEINTRESOURCEW(id), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR)};
	}
	
	template<>
	WHALE_API HCursor FCore::GetCursor<CharA>(int32 id, HInstance hInstance)
	{
		return {::LoadImageA((HINSTANCE) hInstance.handle, MAKEINTRESOURCEA(id), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR)};
	}
	
	template<>
	WHALE_API HCursor FCore::GetCursor<CharW>(int32 id, HInstance hInstance)
	{
		return {::LoadImageW((HINSTANCE) hInstance.handle, MAKEINTRESOURCEW(id), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR)};
	}
	
	
	template<>
	WHALE_API Bool FCore::GainAdminPrivileges(const StringA &strApp)
	{
		SHELLEXECUTEINFOA execInfo;
		execInfo.cbSize = sizeof(execInfo);
		execInfo.lpFile = strApp.CStr();
		execInfo.cbSize = sizeof(execInfo);
		execInfo.lpVerb = "runas";
		execInfo.fMask  = SEE_MASK_NO_CONSOLE;
		execInfo.nShow  = SW_SHOWDEFAULT;
		
		return ::ShellExecuteExA(&execInfo);
	}
	
	
	template<>
	WHALE_API Bool FCore::GainAdminPrivileges(const StringW &strApp)
	{
		SHELLEXECUTEINFOW execInfo;
		execInfo.cbSize = sizeof(execInfo);
		execInfo.lpFile = strApp.CStr();
		execInfo.cbSize = sizeof(execInfo);
		execInfo.lpVerb = L"runas";
		execInfo.fMask  = SEE_MASK_NO_CONSOLE;
		execInfo.nShow  = SW_SHOWDEFAULT;
		
		return ::ShellExecuteExW(&execInfo);
	}
	
	Bool FCore::IsRunAsAdministrator()
	{
		return IsUserAnAdmin();
//		::BOOL fIsRunAsAdmin = FALSE;
//		::DWORD dwError = ERROR_SUCCESS;
//		::PSID pAdministratorsGroup = nullptr;
//
//		::SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
//		if (!::AllocateAndInitializeSid(
//			&NtAuthority,
//			2,
//			SECURITY_BUILTIN_DOMAIN_RID,
//			DOMAIN_ALIAS_RID_ADMINS,
//			0, 0, 0, 0, 0, 0,
//			&pAdministratorsGroup
//		))
//		{
//			dwError = ::GetLastError();
//			goto Cleanup;
//		}
//
//		if (!::CheckTokenMembership(nullptr, pAdministratorsGroup, &fIsRunAsAdmin))
//		{
//			dwError = ::GetLastError();
//			goto Cleanup;
//		}
//
//Cleanup:
//
//		if (pAdministratorsGroup)
//		{
//			::FreeSid(pAdministratorsGroup);
//			pAdministratorsGroup = nullptr;
//		}
//
//		if (ERROR_SUCCESS != dwError)
//		{
//			FDebug::LogError(TagW, MessageToStringW(HRESULT_FROM_WIN32(dwError)).CStr());
//		}
//
//		return fIsRunAsAdmin;
	}
	
	template<>
	WHALE_API StringA FCore::GetCommandLineT()
	{
		return ::GetCommandLineA();
	}
	
	template<>
	WHALE_API StringW FCore::GetCommandLineT()
	{
		return ::GetCommandLineW();
	}
	
	template<>
	WHALE_API StringA FCore::MessageToString(HResult dwMessageId)
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
	
	template<>
	WHALE_API StringW FCore::MessageToString(HResult dwMessageId)
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
	
	FResult FCore::GetLastError()
	{
		return HRESULT_FROM_WIN32(::GetLastError());
	}
	
	
} // Whale