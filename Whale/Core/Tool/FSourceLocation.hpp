//
// Created by admin on 2024/7/15.
//

#pragma once

#include "FTypeDef.hpp"
#include "Whale/Tool/Locale/WLocale.hpp"

namespace Whale
{
	
	struct FSourceLocation
	{
		
		static consteval FSourceLocation Current
			(
				const uint32 line = __builtin_LINE(), const uint32 column = __builtin_COLUMN(),
				const Char *const file = __builtin_FILE(),
				const Char *const function = __builtin_FUNCSIG()
			) noexcept
		{
			FSourceLocation result{};
			result.line = line;
			result.column = column;
			result.file = file;
			result.function = function;
			return result;
		}
		
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
	
} // Whale
