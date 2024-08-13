//
// Created by admin on 2024/8/13.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>

#include "WGenericTime.hpp"

namespace Whale
{
	
	/// 查找数据
	struct WHALE_API FFindData
	{
		FString name;
		Bool    isDir;
		FTime   createTime;
		FTime   lastAccessTime;
		FTime   lastWriteTime;
		SizeT   fileSize;
	};
	
	/// 文件查找器
	class WHALE_API WGenericFileFinder : public WObject
	{
	public:
		
		WGenericFileFinder() = default;
		
		WGenericFileFinder(const WGenericFileFinder &) = delete;
	
	public:
		
		WGenericFileFinder &operator=(const WGenericFileFinder &) = delete;
	
	public:
		
		/// 初始化
		virtual Bool FindFirst(const FString &, FFindData &find) = 0;
		
		/// 查找下一个
		virtual Bool FindNext(FFindData &find) = 0;
		
		/// 关闭
		virtual Bool Close() = 0;
		
	};
	
} // Whale
