//
// Created by admin on 2024/7/17.
//

#pragma once

#include "TypeDef.hpp"
#include <stdexcept>

namespace Whale
{
	
	///
	/// 异常
	class WHALE_API FException : private std::runtime_error
	{
	public:
		
		explicit FException(const Char *message) : std::runtime_error(reinterpret_cast<const char *>(message)) {}
		
		FException() : FException(WTEXT("")) {}
	
	public:
		
		[[nodiscard]] const Char *What() const noexcept { return reinterpret_cast<const Char *>(this->what()); }
		
	};
	
	///
	/// 空指针异常
	class WHALE_API FNullPtrException : public FException
	{
	public:
		
		FNullPtrException() : FException() {}
		
		explicit FNullPtrException(const Char *message) : FException(message) {}
		
	};
	
	
	///
	/// 类型转换异常
	class WHALE_API FInvalidCastException : public FException
	{
	public:
		
		FInvalidCastException() : FException() {}
		
		explicit FInvalidCastException(const Char *message) : FException(message) {}
		
	};
	
	///
	/// IO异常
	class WHALE_API FIOException : public FException
	{
	public:
		
		FIOException() : FException() {}
		
		explicit FIOException(const Char *message) : FException(message) {}
		
	};
	
	///
	/// 访问未知文件的异常
	class WHALE_API FFileNotFoundException : public FException
	{
	public:
		
		FFileNotFoundException() : FException() {}
		
		explicit FFileNotFoundException(const Char *message) : FException(message) {}
		
	};
	
	///
	/// 加载异常
	class WHALE_API FLoadException : public FException
	{
	public:
		
		FLoadException() : FException() {}
		
		explicit FLoadException(const Char *message) : FException(message) {}
		
	};
	
} // Whale
