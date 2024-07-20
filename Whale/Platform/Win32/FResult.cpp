//
// Created by admin on 2024/7/6.
//

#include "FResult.hpp"

#include "Whale/Core/FDebug.hpp"
#include "Whale/Core/WProgram.hpp"
#include "Whale/Platform/Win32/FCore.hpp"

#include <format>

namespace Whale::Win32
{
	
	FResult::~FResult()
	{
		if (isThrowIfFailedAtDestructTime) ThrowIfFailed("Error");
	}
	
	bool FResult::IsFailed() const
	{
		return hr < 0;
	}
	
	bool FResult::IsSucceeded() const
	{
		return hr >= 0;
	}
	
	StringA FResult::ToString(const StringA &message) const
	{
		return std::format(
			"{}: (0x{:08X}): {}", message.CStr(), (uint32) hr, Win32::FCore::MessageToStringA(hr)).c_str();
	}
	
	StringW FResult::ToString(const StringW &message) const
	{
		return std::format(
			L"{}: (0x{:08X}): {}", message.CStr(), (uint32) hr, Win32::FCore::MessageToStringW(hr)).c_str();
	}
	
	void FResult::Throw(const StringA &message, const FSourceLocation &sourceLocation) const
	{
		FDebug::LogFatal(TagA, ToString(message), sourceLocation);
		throw FResultException();
	}
	
	void FResult::Throw(const StringW &message, const FSourceLocation &sourceLocation) const
	{
		FDebug::LogFatal(TagW, ToString(message), sourceLocation);
		throw FResultException();
	}
	
	
	void FResult::ThrowIfFailed(const StringA &message, const FSourceLocation &sourceLocation) const
	{
		if (IsFailed()) Throw(message, sourceLocation);
	}
	
	void FResult::ThrowIfFailed(const StringW &message, const FSourceLocation &sourceLocation) const
	{
		if (IsFailed()) Throw(message, sourceLocation);
	}
	
	
} // Whale