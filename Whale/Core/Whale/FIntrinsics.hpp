//
// Created by admin on 2024/7/17.
//

#pragma once

#include "TypeDef.hpp"

#ifdef WHALE_TARGET_WINDOWS

#include <intrin.h>

#endif

#include <atomic>

namespace Whale
{
	
	using AtomicCounterT = ULong;
	
	#ifdef WHALE_TARGET_WINDOWS
	
	///
	/// 内部函数
	class WHALE_API FIntrinsics
	{
	public:
		
		inline static Short InterlockedIncrement(Short *addend) noexcept
		{
			return ::_InterlockedIncrement16(addend);
		}
		
		inline static Long InterlockedIncrement(Long *addend) noexcept
		{
			return ::_InterlockedIncrement(addend);
		}
		
		inline static Short InterlockedIncrementU(UShort *addend) noexcept
		{
			return ::_InterlockedIncrement16(reinterpret_cast<Short *>(addend));
		}
		
		inline static Long InterlockedIncrementU(ULong *addend) noexcept
		{
			return ::_InterlockedIncrement(reinterpret_cast<Long *>(addend));
		}
		
		inline static Short InterlockedDecrement(Short *addend) noexcept
		{
			return ::_InterlockedDecrement16(addend);
		}
		
		inline static Long InterlockedDecrement(Long *addend) noexcept
		{
			return ::_InterlockedDecrement(addend);
		}
		
		inline static Short InterlockedDecrementU(UShort *addend) noexcept
		{
			return ::_InterlockedDecrement16(reinterpret_cast<Short *>(addend));
		}
		
		inline static Long InterlockedDecrementU(ULong *addend) noexcept
		{
			return ::_InterlockedDecrement(reinterpret_cast<Long *>(addend));
		}
		
		#ifdef WHALE_COMPILER_BIT_64
		
		inline static int64 InterlockedIncrement(int64 *addend) noexcept
		{
			return ::_InterlockedIncrement64(addend);
		}
		
		inline static int64 InterlockedIncrementU(uint64 *addend) noexcept
		{
			return ::_InterlockedIncrement64(reinterpret_cast<int64 *>(addend));
		}
		
		inline static int64 InterlockedDecrement(int64 *addend) noexcept
		{
			return ::_InterlockedDecrement64(addend);
		}
		
		inline static int64 InterlockedDecrementU(uint64 *addend) noexcept
		{
			return ::_InterlockedDecrement64(reinterpret_cast<int64 *>(addend));
		}
		
		#endif
		
	};
	
	#endif
	
} // Whale
