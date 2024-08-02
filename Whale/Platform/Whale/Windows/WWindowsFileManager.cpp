//
// Created by admin on 2024/8/2.
//

#include "WWindowsFileManager.hpp"

#include <Windows.h>

#undef CreateDirectory
#undef MoveFile
#undef RemoveDirectory

namespace Whale
{
	Bool WWindowsFileManager::CreateDirectory(const FString &directoryName)
	{
		SECURITY_ATTRIBUTES securityAttributes{};
		return ::CreateDirectoryW(directoryName.CStr(), &securityAttributes);
	}
	
	Bool WWindowsFileManager::MoveFile(const FString &fileName, const FString &newFileName)
	{
		return ::MoveFileW(fileName.CStr(), newFileName.CStr());
	}
	
	Bool WWindowsFileManager::RemoveDirectory(const FString &directoryName)
	{
		return ::RemoveDirectoryW(directoryName.CStr());
	}
	
} // Whale