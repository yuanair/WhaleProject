//
// Created by admin on 2024/8/2.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>

#include "Windows/HWinDef.hpp"

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
		
		/// 退出
		virtual void Exit(int32 result) const = 0;
		
		/// 获取平台名称
		[[nodiscard]] virtual FString GetName() const = 0;
		
		/// 是否为管理员模式运行
		[[nodiscard]] virtual Bool IsRunAsAdministrator() const = 0;
		
		/// 获取模块句柄
		[[nodiscard]] virtual HModule GetModuleHandle() const = 0;
		
	};
	
	
} // Whale
