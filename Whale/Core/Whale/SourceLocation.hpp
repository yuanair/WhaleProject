//
// Created by admin on 2024/7/15.
//

#pragma once

#include "TypeDef.hpp"
#include "FLocale.hpp"

namespace Whale
{
	
	struct FSourceLocation
	{
#if defined(WHALE_COMPILER_TYPE_MSVC) || defined(WHALE_COMPILER_TYPE_CLANG)
		
		static consteval FSourceLocation Current
			(
				uint32 line = __builtin_LINE(),
				uint32 column = __builtin_COLUMN(),
				const CharA *file = __builtin_FILE(),
				const CharA *function = __builtin_FUNCSIG()
			) noexcept;

#elif defined(WHALE_COMPILER_TYPE_GCC)
		
		static consteval FSourceLocation Current
			(
				uint32 line = __builtin_LINE(),
				uint32 column = 0,
				const CharA *file = __builtin_FILE(),
				const CharA *function = __builtin_FUNCTION()
			) noexcept;

#else
		
		static consteval FSourceLocation Current
			(
				uint32 line = __builtin_LINE(),
				 uint32 column = 0,
				const CharA *file = __builtin_FILE(),
				const CharA *function = __builtin_FUNCTION()
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
		
		uint32      line{};
		uint32      column{};
		const CharA *file     = "";
		const CharA *function = "";
		
	};
	
	consteval FSourceLocation
	FSourceLocation::Current(uint32 line, uint32 column, const CharA *file, const CharA *function) noexcept
	{
		FSourceLocation result{};
		result.line     = line;
		result.column   = column;
		result.file     = file;
		result.function = function;
		return result;
	}
	
} // Whale
