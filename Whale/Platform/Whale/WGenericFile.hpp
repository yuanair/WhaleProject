//
// Created by admin on 2024/8/2.
//

#pragma once


#include <Whale/TypeDef.hpp>
#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>

namespace Whale
{
	
	/// 打开模式
	enum EFileOpenMode : int32
	{
		EFileOpenModeNone = 0x0000,
		
		/// 读模式
		EFileOpenModeRead      = 0x0001,
		/// 写模式
		EFileOpenModeWrite     = 0x0002,
		EFileOpenModeReadWrite = EFileOpenModeRead | EFileOpenModeWrite,
		
		/// 不共享
		EFileSharedNone        = 0x0000,
		/// 共享读模式，二次访问可读文件
		EFileSharedRead        = 0x0010,
		/// 共享写模式，二次访问可写文件
		EFileSharedWrite       = 0x0020,
		/// 共享删除模式，二次访问可删除文件
		EFileSharedDelete      = 0x0040,
		EFileSharedReadWrite   = EFileSharedRead | EFileSharedWrite,
		EFileSharedReadDelete  = EFileSharedRead | EFileSharedDelete,
		EFileSharedWriteDelete = EFileSharedWrite | EFileSharedDelete,
		EFileSharedAll         = EFileSharedRead | EFileSharedWrite | EFileSharedDelete,
		
		/// 不创建文件
		EFileCreateNone    = 0x0000,
		/// 未找到创建文件
		EFileCreateNoFound = 0x0100,
		/// 始终创建文件
		EFileCreateAlways  = 0x0200,
	};
	
	/// 文件
	class WHALE_API WGenericFile : public WObject
	{
	public:
		
		WGenericFile() = default;
		
		WGenericFile(const WGenericFile &) = delete;
	
	public:
		
		WGenericFile &operator=(const WGenericFile &) = delete;
	
	public:
		
		/// 打开文件
		virtual void Open(const FString &fileName, EFileOpenMode openMode) = 0;
		
		/// 关闭文件
		virtual void Close() = 0;
		
	};
	
} // Whale
