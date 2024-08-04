//
// Created by admin on 2024/8/2.
//

#pragma once

#include "HWinDef.hpp"

#include "../WGenericLocale.hpp"

namespace Whale
{
	/// 本地化
	class WHALE_API WWindowsLocale : public WGenericLocale
	{
	public:
		
		static WWindowsLocale &Get();
	
	public:
		
		[[nodiscard]] StringA Between(
			const StringA &str, const FString &fromEncoding, const FString &toEncoding) const override;
		
		[[nodiscard]] FString ToFString(const StringA &str) const override;
		
		[[nodiscard]] StringA ToAString(const FString &str) const override;
		
		[[nodiscard]] FString ToFString(const StringA &str, const FString &encoding) const override;
		
		[[nodiscard]] StringA ToAString(const FString &str, const FString &encoding) const override;
		
		FString ToFString(Bool value) const override;
		
		StringA ToAString(Bool value) const override;
		
		FString ToFString(int32 value) const override;
		
		StringA ToAString(int32 value) const override;
		
		FString ToFString(uint32 value) const override;
		
		StringA ToAString(uint32 value) const override;
		
		FString ToFString(int64 value) const override;
		
		StringA ToAString(int64 value) const override;
		
		FString ToFString(uint64 value) const override;
		
		StringA ToAString(uint64 value) const override;
		
		FString ToFString(Float value) const override;
		
		StringA ToAString(Float value) const override;
		
		FString ToFString(Double value) const override;
		
		StringA ToAString(Double value) const override;
	
	public:
		
		[[nodiscard]] FString ToFString(const StringA &str, Int codePage) const;
		
		[[nodiscard]] StringA ToAString(const FString &str, Int codePage) const;
	
	private:
		
		WWindowsLocale() = default;
		
	};
	
} // Whale
