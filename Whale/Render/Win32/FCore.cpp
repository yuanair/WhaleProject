//
// Created by admin on 2024/7/1.
//

#include "FCore.hpp"
#include "Whale/Core/Debug/FDebug.hpp"
#include "Whale/Core/Object/WProgram.hpp"

#include <windows.h>

namespace Whale::Win32
{
	
	HInstance FCore::ShellExecuteT(HWindow hWnd, const std::string &operation, const std::string &file,
	                               const std::string &parameters,
	                               const std::string &directory, int32 showCmd)
	{
		return {
			::ShellExecuteA((HWND) hWnd.handle, operation.c_str(), file.c_str(), parameters.c_str(), directory.c_str(),
			                showCmd
			)
		};
	}
	
	
	HInstance FCore::ShellExecuteT(HWindow hWnd, const std::wstring &operation, const std::wstring &file,
	                               const std::wstring &parameters,
	                               const std::wstring &directory, int32 showCmd)
	{
		return {
			::ShellExecuteW((HWND) hWnd.handle, operation.c_str(), file.c_str(), parameters.c_str(), directory.c_str(),
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
	
	void FCore::GainAdminPrivileges(const std::string &strApp)
	{
		SHELLEXECUTEINFOA execInfo;
		execInfo.cbSize = sizeof(execInfo);
		execInfo.lpFile = strApp.c_str();
		execInfo.cbSize = sizeof(execInfo);
		execInfo.lpVerb = "runas";
		execInfo.fMask = SEE_MASK_NO_CONSOLE;
		execInfo.nShow = SW_SHOWDEFAULT;
		
		::ShellExecuteExA(&execInfo);
	}
	
	void FCore::GainAdminPrivileges(const std::wstring &strApp)
	{
		SHELLEXECUTEINFOW execInfo;
		execInfo.cbSize = sizeof(execInfo);
		execInfo.lpFile = strApp.c_str();
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
			FDebug::LogError(WProgram::GetAppNameW(), MessageToStringW(HRESULT_FROM_WIN32(dwError)).c_str());
		}
		
		return fIsRunAsAdmin;
	}
	
	
	std::string FCore::GetCommandLineA()
	{
		return ::GetCommandLineA();
	}
	
	std::wstring FCore::GetCommandLineW()
	{
		return ::GetCommandLineW();
	}
	
	std::string FCore::MessageToStringA(HResult dwMessageId)
	{
		auto strBufferError = WHALE_NEW_CLIENT Char[256];
		::FormatMessageA
			(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				nullptr, dwMessageId, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
				strBufferError, 256, nullptr
			);
		std::string buffer = strBufferError;
		delete[] strBufferError;
		return buffer;
	}
	
	std::wstring FCore::MessageToStringW(HResult dwMessageId)
	{
		auto strBufferError = WHALE_NEW_CLIENT WChar[256];
		::FormatMessageW
			(
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				nullptr, dwMessageId, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
				strBufferError, 256, nullptr
			);
		std::wstring buffer = strBufferError;
		delete[] strBufferError;
		return buffer;
	}
	
	HResult FCore::GetLastError()
	{
		return HRESULT_FROM_WIN32(::GetLastError());
	}
	
} // Whale