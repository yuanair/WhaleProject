//
// Created by admin on 2024/8/2.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>

#include "Windows/HWinDef.hpp"
#include "WProgram.hpp"

namespace Whale
{
	
	/// 平台类
	class WHALE_API WGenericPlatform : public WObject
	{
	public:
		
		WGenericPlatform() = default;
		
		WGenericPlatform(const WGenericPlatform &) = delete;
	
	public:
		
		WGenericPlatform &operator=(const WGenericPlatform &) = delete;
	
	public:
		
		/// 运行程序
		virtual int32 Run(WProgram &program) const = 0;
		
		/// 退出
		virtual void Exit(int32 result) const = 0;
		
		/// 获取平台名称
		[[nodiscard]] virtual FString GetName() const = 0;
		
		/// 获取换行符号
		[[nodiscard]] virtual FString GetNewLine() const = 0;
		
		/// 是否为管理员模式运行
		[[nodiscard]] virtual Bool IsRunAsAdministrator() const = 0;
		
		/// 获取模块句柄
		[[nodiscard]] virtual HModule GetModuleHandle() const = 0;
		
		/// 获取窗口管理器
		[[nodiscard]] virtual class WGenericWindowManager &GetWindowManager() const = 0;
		
		/// 获取文件管理器
		[[nodiscard]] virtual class WGenericFileManager &GetFileManager() const = 0;
		
		/// 获取本地化
		[[nodiscard]] virtual class WGenericLocale &GetLocale() const = 0;
		
	};
	
	
} // Whale
