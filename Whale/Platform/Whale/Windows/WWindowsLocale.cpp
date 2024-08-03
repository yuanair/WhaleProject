//
// Created by admin on 2024/8/2.
//

#include "WWindowsLocale.hpp"

#include <Windows.h>

namespace Whale
{
	WWindowsLocale &WWindowsLocale::Get()
	{
		static WWindowsLocale locale;
		return locale;
	}
	
	StringA WWindowsLocale::Between(const StringA &str, const FString &fromEncoding, const FString &toEncoding) const
	{
		return ToAString(ToFString(str, fromEncoding), toEncoding);
	}
	
	FString WWindowsLocale::ToFString(const StringA &str) const
	{
		return ToFString(str, CP_ACP);
	}
	
	StringA WWindowsLocale::ToAString(const FString &str) const
	{
		return ToAString(str, CP_ACP);
	}
	
	FString WWindowsLocale::ToFString(const StringA &str, const FString &encoding) const
	{
		SetThreadLocale(LocaleNameToLCID(encoding.CStr(), 0));
		return ToFString(str, CP_THREAD_ACP);
	}
	
	StringA WWindowsLocale::ToAString(const FString &str, const FString &encoding) const
	{
		SetThreadLocale(LocaleNameToLCID(encoding.CStr(), 0));
		return ToAString(str, CP_THREAD_ACP);
	}
	
	FString WWindowsLocale::ToFString(const StringA &str, Int codePage) const
	{
		int len = MultiByteToWideChar(
			codePage, 0, str.CStr(), static_cast<int>(str.GetLength()), nullptr, 0
		);
		if (len < 0) return {};
		auto *buffer = new Char[len + 1];
		MultiByteToWideChar(
			codePage, 0, str.CStr(), static_cast<int>(str.GetLength()), buffer, len
		);
		buffer[len] = 0;
		FString res{buffer, static_cast<SizeT>(len + 1)};
		delete[] buffer;
		return res;
	}
	
	StringA WWindowsLocale::ToAString(const FString &str, Int codePage) const
	{
		int len = WideCharToMultiByte(
			codePage, 0, str.CStr(), static_cast<int>(str.GetLength()), nullptr, 0, nullptr, nullptr
		);
		if (len <= 0)return {};
		auto *buffer = new CharA[len + 1];
		WideCharToMultiByte(
			codePage, 0, str.CStr(), static_cast<int>(str.GetLength()), buffer, len, nullptr, nullptr
		);
		buffer[len] = 0;
		StringA res{buffer, static_cast<SizeT>(len + 1)};
		delete[] buffer;
		return res;
	}
} // Whale