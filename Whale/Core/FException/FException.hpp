//
// Created by admin on 2024/7/17.
//

#pragma once

#include "Whale/Core/Tool/FTypeDef.hpp"
#include <exception>

namespace Whale
{
	
	///
	/// 异常
	class WHALE_API FException : public std::exception
	{
	public:
		
		FException() : std::exception() {}
		
		explicit FException(const Char *message) : std::exception(message) {}
		
		FException(const Char *message, int) : std::exception(message, 0) {}
		
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
