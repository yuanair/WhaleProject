//
// Created by admin on 2024/7/6.
//

#include "FDirectXResult.hpp"

#include "Whale/Core/Debug/FDebug.hpp"
#include "Whale/Core/Object/WProgram.hpp"
#include "Whale/Render/Win32/FCore.hpp"

#include <format>

namespace Whale
{
	
	FDirectXResult::~FDirectXResult()
	{
		if (isThrowIfFailedAtDestructTime) ThrowIfFailed("Error");
	}
	
	bool FDirectXResult::IsFailed() const
	{
		return hr < 0;
	}
	
	bool FDirectXResult::IsSucceeded() const
	{
		return hr >= 0;
	}
	
	StringA FDirectXResult::ToString(const StringA &message) const
	{
		return std::format(
			"{}: (0x{:08X}): {}", message.CStr(), (uint32) hr, Win32::FCore::MessageToStringA(hr)).c_str();
	}
	
	StringW FDirectXResult::ToString(const StringW &message) const
	{
		return std::format(
			L"{}: (0x{:08X}): {}", message.CStr(), (uint32) hr, Win32::FCore::MessageToStringW(hr)).c_str();
	}
	
	void FDirectXResult::Throw(const StringA &message, const FSourceLocation &sourceLocation) const
	{
		FDebug::LogFatal(WProgram::GetAppNameA(), ToString(message), sourceLocation);
		throw FDirectXResultException();
	}
	
	void FDirectXResult::Throw(const StringW &message, const FSourceLocation &sourceLocation) const
	{
		FDebug::LogFatal(WProgram::GetAppNameW(), ToString(message), sourceLocation);
		throw FDirectXResultException();
	}
	
	
	void FDirectXResult::ThrowIfFailed(const StringA &message, const FSourceLocation &sourceLocation) const
	{
		if (IsFailed()) Throw(message, sourceLocation);
	}
	
	void FDirectXResult::ThrowIfFailed(const StringW &message, const FSourceLocation &sourceLocation) const
	{
		if (IsFailed()) Throw(message, sourceLocation);
	}
	
	
} // Whale