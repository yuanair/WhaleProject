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
	enum EFileOpenMode
	{
		/// None
		EFileOpenModeNone      = 0x0000,
		/// 读模式
		EFileOpenModeRead      = 0x0001,
		/// 写模式
		EFileOpenModeWrite     = 0x0002,
		EFileOpenModeReadWrite = EFileOpenModeRead | EFileOpenModeWrite,
	};
	
	/// 共享模式
	enum EFileSharedMode
	{
		/// 不共享
		EFileSharedModeNone        = 0x0000,
		/// 共享读模式，二次访问可读文件
		EFileSharedModeRead        = 0x0010,
		/// 共享写模式，二次访问可写文件
		EFileSharedModeWrite       = 0x0020,
		/// 共享删除模式，二次访问可删除文件
		EFileSharedModeDelete      = 0x0040,
		EFileSharedModeReadWrite   = EFileSharedModeRead | EFileSharedModeWrite,
		EFileSharedModeReadDelete  = EFileSharedModeRead | EFileSharedModeDelete,
		EFileSharedModeWriteDelete = EFileSharedModeWrite | EFileSharedModeDelete,
		EFileSharedModeAll         = EFileSharedModeRead | EFileSharedModeWrite | EFileSharedModeDelete,
	};
	
	/// 创建模式
	enum EFileCreateMode
	{
		/// 不创建文件
		EFileCreateModeNone    = 0x0000,
		/// 未找到创建文件
		EFileCreateModeNoFound = 0x0100,
		/// 始终创建文件
		EFileCreateModeAlways  = 0x0200,
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
		
		/// 是否已打开
		[[nodiscard]] virtual Bool IsOpened() const = 0;
		
		/// 打开文件
		virtual void Open(
			const FString &fileName, EFileOpenMode openMode,
			EFileSharedMode sharedMode = EFileSharedModeNone,
			EFileCreateMode createMode = EFileCreateModeNone
		) = 0;
		
		/// 打开文件
		virtual void Open(
			const StringA &fileName, EFileOpenMode openMode,
			EFileSharedMode sharedMode = EFileSharedModeNone,
			EFileCreateMode createMode = EFileCreateModeNone
		) = 0;
		
		/// 写入字符
		virtual Bool Write(Char ch) = 0;
		
		/// 写入字符串
		virtual Bool Write(const FString &str) = 0;
		
		/// 写入换行
		virtual Bool WriteLine() = 0;
		
		/// 写入字符串，并换行
		virtual Bool WriteLine(const FString &str) = 0;
		
		/// 写入字符
		virtual Bool Write(CharA ch) = 0;
		
		/// 写入字符串
		virtual Bool Write(const StringA &str) = 0;
		
		/// 写入字符串，并换行
		virtual Bool WriteLine(const StringA &str) = 0;
		
		/// 读取字符
		virtual Bool Read(Char &ch) = 0;
		
		/// 读取字符串
		virtual Bool Read(FString &str) = 0;
		
		/// 读取字符
		virtual Bool Read(CharA &ch) = 0;
		
		/// 读取字符串
		virtual Bool Read(StringA &str) = 0;
		
		/// 设置位置为开始
		virtual Bool SetPosToBegin() = 0;
		
		/// 设置位置为结束
		virtual Bool SetPosToEnd() = 0;
		
		/// 刷新缓冲区
		virtual Bool Flush() = 0;
		
		/// 关闭文件
		virtual void Close() = 0;
		
	};
	
} // Whale
