//
// Created by admin on 2024/7/6.
//

#include "FResult.hpp"

#include "Whale/FDebug.hpp"
#include "FCore.hpp"
#include "../FPlatformManager.hpp"

#include <format>

namespace Whale
{
	
	FResult::~FResult()
	{
		if (m_isThrowIfFailedAtDestructTime) ThrowIfFailed("Error");
	}
	
	bool FResult::IsFailed() const
	{
		return m_hr < 0;
	}
	
	bool FResult::IsSucceeded() const
	{
		return m_hr >= 0;
	}
	
	StringA FResult::ToString(const StringA &message) const
	{
		return std::format(
			"{}: (0x{:08X}): {}", message.CStr(), (uint32) m_hr,
			FCore::MessageToString<CharA>(m_hr).CStr()).c_str();
	}
	
	StringW FResult::ToString(const StringW &message) const
	{
		return std::format(
			L"{}: (0x{:08X}): {}", message.CStr(), (uint32) m_hr,
			FCore::MessageToString<CharW>(m_hr).CStr()).c_str();
	}
	
	void FResult::Log(const StringA &message, const FSourceLocation &sourceLocation)
	{
		m_isThrowIfFailedAtDestructTime = false;
		StringA buffer = ToString(message);
		FDebug::Log<CharA>(Error, logTagA, buffer, sourceLocation);
	}
	
	void FResult::Log(const StringW &message, const FSourceLocation &sourceLocation)
	{
		m_isThrowIfFailedAtDestructTime = false;
		StringW buffer = ToString(message);
		FDebug::Log<CharW>(Error, logTagW, buffer, sourceLocation);
	}
	
	void FResult::Throw(const StringA &message, const FSourceLocation &sourceLocation)
	{
		m_isThrowIfFailedAtDestructTime = false;
		StringA buffer = ToString(message);
		FDebug::Log<CharA>(Fatal, logTagA, buffer, sourceLocation);
		throw FResultException(buffer.CStr());
	}
	
	void FResult::Throw(const StringW &message, const FSourceLocation &sourceLocation)
	{
		m_isThrowIfFailedAtDestructTime = false;
		StringW buffer = ToString(message);
		FDebug::Log<CharW>(Fatal, logTagW, buffer, sourceLocation);
		throw FResultException(FPlatformManager::Get().GetLocale().ToAString(buffer).CStr());
	}
	
	
	void FResult::ThrowIfFailed(const StringA &message, const FSourceLocation &sourceLocation)
	{
		if (IsFailed()) Throw(message, sourceLocation);
	}
	
	void FResult::ThrowIfFailed(const StringW &message, const FSourceLocation &sourceLocation)
	{
		if (IsFailed()) Throw(message, sourceLocation);
	}
	
	void FResult::LogIfFailed(const StringA &message, const FSourceLocation &sourceLocation)
	{
		if (IsFailed()) Log(message, sourceLocation);
	}
	
	void FResult::LogIfFailed(const StringW &message, const FSourceLocation &sourceLocation)
	{
		if (IsFailed()) Log(message, sourceLocation);
	}
	
	
} // Whale