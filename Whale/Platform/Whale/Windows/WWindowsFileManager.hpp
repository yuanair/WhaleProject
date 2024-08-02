//
// Created by admin on 2024/8/2.
//

#pragma once

#include "HWinDef.hpp"
#include "../WGenericFileManager.hpp"

namespace Whale
{
	
	class WHALE_API WWindowsFileManager : public WGenericFileManager
	{
	public:
		
		//WGenericFile *OpenFile(const FString &fileName, EFileOpenMode openMode) override;
		
		Bool CreateDirectory(const FString &directoryName) override;
		
		Bool MoveFile(const FString &fileName, const FString &newFileName) override;
		
		Bool RemoveDirectory(const FString &directoryName) override;
		
	};
	
	typedef WWindowsFileManager WFileManager;
	
} // Whale
