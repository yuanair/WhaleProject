//
// Created by admin on 2024/7/6.
//

#include "FResult.hpp"

#include "Whale/FDebug.hpp"
#include "FCore.hpp"

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
			Windows::FCore::MessageToString<CharA>(m_hr).CStr()).c_str();
	}
	
	StringW FResult::ToString(const StringW &message) const
	{
		return std::format(
			L"{}: (0x{:08X}): {}", message.CStr(), (uint32) m_hr,
			Windows::FCore::MessageToString<CharW>(m_hr).CStr()).c_str();
	}
	
	void FResult::Throw(const StringA &message, const FSourceLocation &sourceLocation)
	{
		m_isThrowIfFailedAtDestructTime = false;
		StringA buffer = ToString(message);
		FDebug::Log<CharA>(Fatal, TagA, buffer, sourceLocation);
		throw FResultException(buffer.CStr());
	}
	
	void FResult::Throw(const StringW &message, const FSourceLocation &sourceLocation)
	{
		m_isThrowIfFailedAtDestructTime = false;
		StringW buffer = ToString(message);
		FDebug::Log<CharW>(Fatal, TagW, buffer, sourceLocation);
		throw FResultException(FLocale::UTFToString(buffer, "UTF-8").CStr());
	}
	
	
	void FResult::ThrowIfFailed(const StringA &message, const FSourceLocation &sourceLocation)
	{
		if (IsFailed()) Throw(message, sourceLocation);
	}
	
	void FResult::ThrowIfFailed(const StringW &message, const FSourceLocation &sourceLocation)
	{
		if (IsFailed()) Throw(message, sourceLocation);
	}
	
	
} // Whale