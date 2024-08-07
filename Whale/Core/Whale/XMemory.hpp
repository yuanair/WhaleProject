//
// Created by admin on 2024/8/7.
//

#pragma once

#include "TypeDef.hpp"

namespace Whale
{
	
	/// 内存移动
	WHALE_API inline void *MemoryMove(void *dest, const void *source, SizeT size) noexcept;
	
	/// 内存拷贝
	WHALE_API inline void *MemoryCopy(void *dest, const void *source, SizeT size) noexcept;
	
} // Whale
