//
// Created by admin on 2024/7/6.
//

#include "FDirectXResult.hpp"

#include "Whale/Core/Debug/FDebug.hpp"
#include "Whale/Core/Object/WProgram.hpp"

#include <format>

namespace Whale
{
	FDirectXResult::FDirectXResult(int32 hr)
		: hr(hr)
	{
	
	}
	
	FDirectXResult::~FDirectXResult()
	{
		if (isThrowIfFailedAtDestructTime) ThrowIfFailed("Error");
	}
	
	int32 FDirectXResult::GetHr() const
	{
		return hr;
	}
	
	bool FDirectXResult::IsFailed() const
	{
		return hr < 0;
	}
	
	bool FDirectXResult::IsSucceeded() const
	{
		return hr >= 0;
	}
	
	FTStringA FDirectXResult::ToString(const FTStringA &message) const
	{
		return std::format(
			"{}: (0x{:08X}): {}", message.CStr(), (uint32) hr, Win32::FCore::MessageToStringA(hr)).c_str();
	}
	
	FTStringW FDirectXResult::ToString(const FTStringW &message) const
	{
		return std::format(
			L"{}: (0x{:08X}): {}", message.CStr(), (uint32) hr, Win32::FCore::MessageToStringW(hr)).c_str();
	}
	
	void FDirectXResult::Throw(const FTStringA &message) const
	{
		FDebug::LogFatal(WProgram::GetAppNameA(), ToString(message));
		throw;
	}
	
	void FDirectXResult::Throw(const FTStringW &message) const
	{
		FDebug::LogFatal(WProgram::GetAppNameW(), ToString(message));
		throw;
	}
	
	
	void FDirectXResult::ThrowIfFailed(const FTStringA &message) const
	{
		if (IsFailed()) Throw(message);
	}
	
	void FDirectXResult::ThrowIfFailed(const FTStringW &message) const
	{
		if (IsFailed()) Throw(message);
	}
	
	bool FDirectXResult::IsThrowIfFailedAtDestructTime() const
	{
		return isThrowIfFailedAtDestructTime;
	}
	
	void FDirectXResult::SetIsThrowIfFailedAtDestructTime(bool isThrowIfFailedAtDestructTime)
	{
		FDirectXResult::isThrowIfFailedAtDestructTime = isThrowIfFailedAtDestructTime;
	}
} // Whale