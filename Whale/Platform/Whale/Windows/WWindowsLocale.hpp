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
	
	public:
		
		[[nodiscard]] FString ToFString(const StringA &str, Int codePage) const;
		
		[[nodiscard]] StringA ToAString(const FString &str, Int codePage) const;
	
	private:
		
		WWindowsLocale() = default;
		
	};
	
	typedef WWindowsLocale WLocale;
	
} // Whale
