//
// Created by admin on 2024/8/13.
//

#include "WWindowsFileFinder.hpp"

#include "WWindowsTime.hpp"

#include <Windows.h>

namespace Whale
{
	WWindowsFileFinder::~WWindowsFileFinder()
	{
		Close();
	}
	
	void ToFindData(const WIN32_FIND_DATAW &source, FFindData &target)
	{
		target.name  = source.cFileName;
		target.isDir = source.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
		WWindowsTime::FileTimeToFTime(target.createTime, source.ftCreationTime);
		WWindowsTime::FileTimeToFTime(target.lastAccessTime, source.ftLastAccessTime);
		WWindowsTime::FileTimeToFTime(target.lastWriteTime, source.ftLastWriteTime);
		target.fileSize = ULARGE_INTEGER{.HighPart = source.nFileSizeHigh, .LowPart=source.nFileSizeLow}.QuadPart;
	}
	
	Bool WWindowsFileFinder::FindFirst(const FString &string, FFindData &find)
	{
		WIN32_FIND_DATAW data;
		m_handle.handle = ::FindFirstFileW(string.CStr(), &data);
		ToFindData(data, find);
		return m_handle.handle != INVALID_HANDLE_VALUE;
	}
	
	Bool WWindowsFileFinder::FindNext(FFindData &find)
	{
		WIN32_FIND_DATAW data;
		auto             result = ::FindNextFileW(m_handle.handle, &data);
		ToFindData(data, find);
		return result;
	}
	
	Bool WWindowsFileFinder::Close()
	{
		if (m_handle.handle == nullptr) return true;
		auto result = ::FindClose(m_handle.handle);
		m_handle.handle = nullptr;
		return result;
	}
} // Whale