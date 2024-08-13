//
// Created by admin on 2024/8/13.
//

#include "FBuild.hpp"

#include <Whale/FPlatformManager.hpp>
#include <Whale/WGenericFileFinder.hpp>
#include <Whale/FCore.hpp>

namespace Whale
{
	void FBuild::Build(const BuildArg &arg)
	{
		TFUniquePtr<WGenericFile> file{
			FPlatformManager::Get().GetFileManager().OpenFile(
				arg.outFile, EFileOpenModeWrite, EFileSharedModeRead, EFileCreateModeNoFound
			)
		};
		file->SetPosToBegin();
		file->Write("# ");
		file->Write(FCore::GetAppName());
		file->Write(" ");
		file->Write(FCore::GetVersion());
		file->WriteLine();
		
		TFUniquePtr<WGenericFileFinder> fileFinder{FPlatformManager::Get().GetFileManager().PreFindFile()};
		FFindData                       data;
		
		fileFinder->FindFirst(arg.buildDir + WTEXT("/*.*"), data);
		
	}
} // Whale