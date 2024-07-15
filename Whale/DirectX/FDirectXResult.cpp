//
// Created by admin on 2024/7/6.
//

#include "FDirectXResult.hpp"

#include "Whale/Core/FDebug.hpp"

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
	
	std::string FDirectXResult::ToString(const std::string &message) const
	{
		return std::format("{}: (0x{:08X}): {}", message, (uint32) hr, Win32::FCore::MessageToStringA(hr));
	}
	
	std::wstring FDirectXResult::ToString(const std::wstring &message) const
	{
		return std::format(L"{}: (0x{:08X}): {}", message, (uint32) hr, Win32::FCore::MessageToStringW(hr));
	}
	
	void FDirectXResult::Throw(const std::string &message) const
	{
		FDebug::LogFatal(ToString(message).c_str());
		throw;
	}
	
	void FDirectXResult::Throw(const std::wstring &message) const
	{
		FDebug::LogFatal(ToString(message).c_str());
		throw;
	}
	
	
	void FDirectXResult::ThrowIfFailed(const std::string &message) const
	{
		if (IsFailed()) Throw(message);
	}
	
	void FDirectXResult::ThrowIfFailed(const std::wstring &message) const
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