//
// Created by admin on 2024/8/7.
//

#include "XMemory.hpp"

#include <cstring>

namespace Whale
{
	
	void *MemoryMove(void *dest, const void *source, SizeT size) noexcept
	{
		return ::memmove(dest, source, size);
	}
	
	void *MemoryCopy(void *dest, const void *source, SizeT size) noexcept
	{
		return ::memcpy(dest, source, size);
	}
	
} // Whale