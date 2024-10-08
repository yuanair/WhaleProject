//
// Created by admin on 2024/8/2.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>

namespace Whale
{
	
	/// 本地化管理器
	class WHALE_API WGenericLocale : public WObject
	{
	public:
		
		WGenericLocale() = default;
		
		WGenericLocale(const WGenericLocale &) = delete;
	
	public:
		
		WGenericLocale &operator=(const WGenericLocale &) = delete;
	
	public:
		
		/// 转换字符编码
		[[nodiscard]] virtual StringA
		Between(const StringA &str, const FString &fromEncoding, const FString &toEncoding) const = 0;
		
		/// 转换为FString
		[[nodiscard]] virtual FString ToFString(const StringA &str) const = 0;
		
		/// 转换为AString
		[[nodiscard]] virtual StringA ToAString(const FString &str) const = 0;
		
		/// 转换为FString
		[[nodiscard]] virtual FString ToFString(const StringA &str, const FString &encoding) const = 0;
		
		/// 转换为AString
		[[nodiscard]] virtual StringA ToAString(const FString &str, const FString &encoding) const = 0;
		
		/// 转换为FString
		[[nodiscard]] virtual FString ToFString(Bool value) const = 0;
		
		/// 转换为AString
		[[nodiscard]] virtual StringA ToAString(Bool value) const = 0;
		
		/// 转换为FString
		[[nodiscard]] virtual FString ToFString(int32 value) const = 0;
		
		/// 转换为AString
		[[nodiscard]] virtual StringA ToAString(int32 value) const = 0;
		
		/// 转换为FString
		[[nodiscard]] virtual FString ToFString(uint32 value) const = 0;
		
		/// 转换为AString
		[[nodiscard]] virtual StringA ToAString(uint32 value) const = 0;
		
		/// 转换为FString
		[[nodiscard]] virtual FString ToFString(int64 value) const = 0;
		
		/// 转换为AString
		[[nodiscard]] virtual StringA ToAString(int64 value) const = 0;
		
		/// 转换为FString
		[[nodiscard]] virtual FString ToFString(uint64 value) const = 0;
		
		/// 转换为AString
		[[nodiscard]] virtual StringA ToAString(uint64 value) const = 0;
		
		/// 转换为FString
		[[nodiscard]] virtual FString ToFString(Float value) const = 0;
		
		/// 转换为AString
		[[nodiscard]] virtual StringA ToAString(Float value) const = 0;
		
		/// 转换为FString
		[[nodiscard]] virtual FString ToFString(Double value) const = 0;
		
		/// 转换为AString
		[[nodiscard]] virtual StringA ToAString(Double value) const = 0;
		
	};
	
} // Whale
