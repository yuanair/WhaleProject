//
// Created by admin on 2024/7/15.
//

#pragma once

#include "HTypeDef.hpp"
#include "WLocale.hpp"

namespace Whale
{
	
	struct FSourceLocation
	{
#if WHALE_COMPILER_TYPE == WHALE_COMPILER_TYPE_MSVC || WHALE_COMPILER_TYPE == WHALE_COMPILER_TYPE_CLANG
		
		static consteval FSourceLocation Current
			(
				uint32 line = __builtin_LINE(),
				uint32 column = __builtin_COLUMN(),
				const Char *file = __builtin_FILE(),
				const Char *function = __builtin_FUNCSIG()
			) noexcept;

#elif WHALE_COMPILER_TYPE == WHALE_COMPILER_TYPE_GCC
		
		static consteval FSourceLocation Current
			(
				uint32 line = __builtin_LINE(),
				uint32 column = 0,
				const Char *file = __builtin_FILE(),
				const Char *function = __builtin_FUNCTION()
			) noexcept;

#else
		
		static consteval FSourceLocation Current
			(
				uint32 line = __builtin_LINE(),
				 uint32 column = 0,
				const Char *file = __builtin_FILE(),
				const Char *function = __builtin_FUNCTION()
			) noexcept;

#endif
		
		
		constexpr FSourceLocation() noexcept = default;
		
		[[nodiscard]]
		constexpr uint32 Line() const noexcept
		{
			return line;
		}
		
		[[nodiscard]]
		constexpr uint32 Column() const noexcept
		{
			return column;
		}
		
		[[nodiscard]]
		constexpr const char *FileName() const noexcept
		{
			return file;
		}
		
		[[nodiscard]]
		constexpr const char *FunctionName() const noexcept
		{
			return function;
		}
	
	private:
		
		uint32 line{};
		uint32 column{};
		const Char *file = "";
		const Char *function = "";
		
	};
	
	consteval FSourceLocation
	FSourceLocation::Current(uint32 line, uint32 column, const Char *file, const Char *function) noexcept
	{
		FSourceLocation result{};
		result.line = line;
		result.column = column;
		result.file = file;
		result.function = function;
		return result;
	}
	
} // Whale
