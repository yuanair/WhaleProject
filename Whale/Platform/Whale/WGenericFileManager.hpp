//
// Created by admin on 2024/8/2.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/Container/TFString.hpp>
#include <Whale/WObject.hpp>
#include "WGenericFile.hpp"

namespace Whale
{
	
	/// 文件管理器
	class WHALE_API WGenericFileManager : public WObject
	{
	public:
		
		/// 新建文件
		virtual WGenericFile *PreOpenFile() = 0;
		
		/// 打开文件
		virtual WGenericFile *OpenFile(const FString &fileName, EFileOpenMode openMode) = 0;
		
		/// 创建文件夹
		virtual Bool CreateDirectory(const FString &directoryName) = 0;
		
		/// 移动文件（夹）
		virtual Bool MoveFile(const FString &fileName, const FString &newFileName) = 0;
		
		/// 删除文件夹
		virtual Bool RemoveDirectory(const FString &directoryName) = 0;
		
	};
	
} // Whale
