//
// Created by admin on 2024/8/2.
//

#include "WWindowsFileManager.hpp"
#include "WWindowsFile.hpp"
#include "WWindowsFileFinder.hpp"

#include <Windows.h>

#undef CreateDirectory
#undef MoveFile
#undef RemoveDirectory

namespace Whale
{
	WGenericFile *WWindowsFileManager::PreOpenFile()
	{
		return WHALE_NEW_CLIENT WWindowsFile();
	}
	
	WGenericFile *
	WWindowsFileManager::OpenFile(const FString &fileName, EFileOpenMode openMode, EFileSharedMode sharedMode,
	                              EFileCreateMode createMode)
	{
		return WHALE_NEW_CLIENT WWindowsFile(fileName, openMode, sharedMode, createMode);
	}
	
	WGenericFileFinder *WWindowsFileManager::PreFindFile()
	{
		return WHALE_NEW_CLIENT WWindowsFileFinder();
	}
	
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
	
	WWindowsFileManager &WWindowsFileManager::Get()
	{
		static WWindowsFileManager fileManager;
		return fileManager;
	}
	
	
} // Whale