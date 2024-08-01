//
// Created by admin on 2024/8/1.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"

namespace Whale
{
	
	/// 应用
	class WHALE_API FApplication
	{
	public:
		
		/// 是否为管理员模式运行
		static Bool IsRunAsAdministrator() noexcept;
		
		/// 退出
		static void Exit(int32 result = 0) noexcept;
		
	};
	
} // Whale
