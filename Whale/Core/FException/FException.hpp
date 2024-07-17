//
// Created by admin on 2024/7/17.
//

#pragma once

#include "Whale/Core/Tool/FTypeDef.hpp"
#include <stdexcept>

namespace Whale
{
	
	///
	/// 异常
	class WHALE_API FException : public std::runtime_error
	{
	public:
		
		FException() : std::runtime_error("") {}
		
		explicit FException(const Char *message) : std::runtime_error(message) {}
		
	};
	
	///
	/// 空指针异常
	class WHALE_API FNullPtrException : public FException
	{
	public:
		
		FNullPtrException() : FException() {}
		
		explicit FNullPtrException(const Char *message) : FException(message) {}
		
	};
	
} // Whale
