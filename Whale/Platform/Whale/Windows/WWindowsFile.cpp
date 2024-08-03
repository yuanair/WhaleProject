//
// Created by admin on 2024/8/2.
//

#include "WWindowsFile.hpp"
#include "WWindowsPlatform.hpp"

#include <Windows.h>

namespace Whale
{
	WWindowsFile::WWindowsFile()
		: m_handle(nullptr)
	{
	
	}
	
	WWindowsFile::WWindowsFile(const FString &fileName, EFileOpenMode openMode)
		: WWindowsFile()
	{
		Open(fileName, openMode);
	}
	
	WWindowsFile::~WWindowsFile()
	{
		Close();
	}
	
	Bool WWindowsFile::IsOpened() const
	{
		return m_handle.handle != nullptr && m_handle.handle != INVALID_HANDLE_VALUE;
	}
	
	void WWindowsFile::Open(const FString &fileName, EFileOpenMode openMode,
	                        EFileSharedMode sharedMode, EFileCreateMode createMode)
	{
		LPSECURITY_ATTRIBUTES lpSecurityAttributes  = nullptr;
		DWORD                 dwDesiredAccess       = 0,
		                      dwShareMode           = 0,
		                      dwCreationDisposition = 0,
		                      dwFlagsAndAttributes  = FILE_ATTRIBUTE_NORMAL;
		HANDLE                hTemplateFile         = nullptr;
		dwDesiredAccess |= openMode & EFileOpenModeRead ? GENERIC_READ : 0;
		dwDesiredAccess |= openMode & EFileOpenModeWrite ? GENERIC_WRITE : 0;
		dwShareMode |= sharedMode & EFileSharedModeRead ? FILE_SHARE_READ : 0;
		dwShareMode |= sharedMode & EFileSharedModeWrite ? FILE_SHARE_WRITE : 0;
		dwShareMode |= sharedMode & EFileSharedModeDelete ? FILE_SHARE_DELETE : 0;
		dwCreationDisposition                       = createMode & EFileCreateModeNoFound ? OPEN_ALWAYS : (
			createMode & EFileCreateModeAlways ? CREATE_ALWAYS : OPEN_EXISTING
		);
		m_handle.handle = ::CreateFileW(
			fileName.CStr(), dwDesiredAccess, dwShareMode,
			lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile
		);
	}
	
	void WWindowsFile::Open(const StringA &fileName, EFileOpenMode openMode,
	                        EFileSharedMode sharedMode, EFileCreateMode createMode)
	{
		LPSECURITY_ATTRIBUTES lpSecurityAttributes  = nullptr;
		DWORD                 dwDesiredAccess       = 0,
		                      dwShareMode           = 0,
		                      dwCreationDisposition = 0,
		                      dwFlagsAndAttributes  = FILE_ATTRIBUTE_NORMAL;
		HANDLE                hTemplateFile         = nullptr;
		dwDesiredAccess |= openMode & EFileOpenModeRead ? GENERIC_READ : 0;
		dwDesiredAccess |= openMode & EFileOpenModeWrite ? GENERIC_WRITE : 0;
		dwShareMode |= sharedMode & EFileSharedModeRead ? FILE_SHARE_READ : 0;
		dwShareMode |= sharedMode & EFileSharedModeWrite ? FILE_SHARE_WRITE : 0;
		dwShareMode |= sharedMode & EFileSharedModeDelete ? FILE_SHARE_DELETE : 0;
		dwCreationDisposition                       = createMode & EFileCreateModeNoFound ? OPEN_ALWAYS : (
			createMode & EFileCreateModeAlways ? CREATE_ALWAYS : OPEN_EXISTING
		);
		m_handle.handle = ::CreateFileA(
			fileName.CStr(), dwDesiredAccess, dwShareMode,
			lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile
		);
	}
	
	Bool WWindowsFile::Write(Char ch)
	{
		DWORD number;
		union A
		{
			CharW chW;
			CharA chA[2];
		}     a;
		a.chW = ch;
		
		if ((ch & 0xFF00) == 0x0000) return ::WriteFile(m_handle.handle, &ch, 1, &number, nullptr);
		// if (a.chA[1] == 0) return ::WriteFile(m_handle.handle, &ch, 1, &number, nullptr);
		
		return ::WriteFile(m_handle.handle, &ch, sizeof(ch) * 1, &number, nullptr);
	}
	
	Bool WWindowsFile::Write(const FString &str)
	{
		for (auto &item: str)
		{
			if (!Write(item)) return false;
		}
		return true;
	}
	
	Bool WWindowsFile::WriteLine()
	{
		return Write(WWindowsPlatform::Get().GetNewLine());
	}
	
	Bool WWindowsFile::WriteLine(const FString &str)
	{
		if (!Write(str))return false;
		return Write(WWindowsPlatform::Get().GetNewLine());
	}
	
	Bool WWindowsFile::Write(CharA ch)
	{
		DWORD number;
		return ::WriteFile(m_handle.handle, &ch, sizeof(ch) * 1, &number, nullptr);
	}
	
	Bool WWindowsFile::Write(const StringA &str)
	{
		DWORD number;
		return ::WriteFile(m_handle.handle, str.CStr(), sizeof(*str.CStr()) * str.GetLength(), &number, nullptr);
	}
	
	Bool WWindowsFile::WriteLine(const StringA &str)
	{
		if (!Write(str))return false;
		return Write(WWindowsPlatform::Get().GetNewLine());
	}
	
	Bool WWindowsFile::Read(Char &ch)
	{
		DWORD number;
		return ::ReadFile(m_handle.handle, &ch, sizeof(ch) * 1, &number, nullptr);
	}
	
	Bool WWindowsFile::Read(FString &str)
	{
		DWORD number;
		return ::ReadFile(m_handle.handle, str.GetPtr(), sizeof(*str.CStr()) * str.GetLength(), &number, nullptr);
	}
	
	Bool WWindowsFile::Read(CharA &ch)
	{
		DWORD number;
		return ::ReadFile(m_handle.handle, &ch, sizeof(ch) * 1, &number, nullptr);
	}
	
	Bool WWindowsFile::Read(StringA &str)
	{
		DWORD number;
		return ::ReadFile(m_handle.handle, str.GetPtr(), sizeof(*str.CStr()) * str.GetLength(), &number, nullptr);
	}
	
	Bool WWindowsFile::Flush()
	{
		return ::FlushFileBuffers(m_handle.handle);
	}
	
	void WWindowsFile::Close()
	{
		if (m_handle.handle) ::CloseHandle(m_handle.handle);
		m_handle.handle = nullptr;
	}
} // Whale