//
// Created by admin on 2024/8/2.
//

#pragma once

#include "HWinDef.hpp"
#include "../WGenericFileManager.hpp"
#include "../WGenericFileFinder.hpp"

namespace Whale
{
	
	class WHALE_API WWindowsFileManager : public WGenericFileManager
	{
	public:
		
		static WWindowsFileManager &Get();
	
	public:
		
		WGenericFile *PreOpenFile() override;
		
		WGenericFile *OpenFile(const FString &fileName, EFileOpenMode openMode, EFileSharedMode sharedMode,
		                       EFileCreateMode createMode) override;
		
		WGenericFileFinder *PreFindFile() override;
		
		Bool CreateDirectory(const FString &directoryName) override;
		
		Bool MoveFile(const FString &fileName, const FString &newFileName) override;
		
		Bool RemoveDirectory(const FString &directoryName) override;
	
	private:
		
		WWindowsFileManager() = default;
		
	};
	
} // Whale
