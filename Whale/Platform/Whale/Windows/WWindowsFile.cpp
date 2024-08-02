//
// Created by admin on 2024/8/2.
//

#include "WWindowsFile.hpp"

#include <Windows.h>

namespace Whale
{
	void WWindowsFile::Open(const FString &fileName, EFileOpenMode openMode)
	{
		LPSECURITY_ATTRIBUTES lpSecurityAttributes  = nullptr;
		DWORD                 dwDesiredAccess       = 0,
		                      dwShareMode           = 0,
		                      dwCreationDisposition = OPEN_EXISTING,
		                      dwFlagsAndAttributes  = FILE_ATTRIBUTE_NORMAL;
		HANDLE                hTemplateFile         = nullptr;
		dwDesiredAccess |= openMode & EFileOpenModeRead ? GENERIC_READ : 0;
		dwDesiredAccess |= openMode & EFileOpenModeWrite ? GENERIC_WRITE : 0;
		dwShareMode |= openMode & EFileSharedRead ? FILE_SHARE_READ : 0;
		dwShareMode |= openMode & EFileSharedWrite ? FILE_SHARE_WRITE : 0;
		dwShareMode |= openMode & EFileSharedDelete ? FILE_SHARE_DELETE : 0;
		dwCreationDisposition |= openMode & EFileCreateNoFound ? OPEN_ALWAYS : 0;
		dwCreationDisposition |= openMode & EFileCreateAlways ? CREATE_ALWAYS : 0;
		m_handle.handle = ::CreateFileW(
			fileName.CStr(), dwDesiredAccess, dwShareMode,
			lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile
		);
	}
	
	void WWindowsFile::Close()
	{
		::CloseHandle(m_handle.handle);
	}
} // Whale