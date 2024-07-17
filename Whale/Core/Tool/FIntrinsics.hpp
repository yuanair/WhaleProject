//
// Created by admin on 2024/7/17.
//

#pragma once

#include "Whale/Core/Tool/FTypeDef.hpp"
#include <intrin.h>
#include <atomic>

namespace Whale
{
	
	using AtomicCounterT = ULong;
	
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
		
		#if WHALE_COMPILER_BIT >= WHALE_COMPILER_64_BIT
		
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
	
} // Whale
