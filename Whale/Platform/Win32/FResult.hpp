//
// Created by admin on 2024/7/6.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"
#include "Whale/Core/Container/TFString.hpp"
#include "Whale/Core/SourceLocation.hpp"
#include "Whale/Core/Exception.hpp"
#include "Whale/Platform/Win32/HWinDef.hpp"

namespace Whale::Win32
{
	
	class FResultException : public FException
	{
	public:
		
		FResultException()
			: FException() {}
		
		explicit FResultException(const CharA *message)
			: FException(message) {}
		
	};
	
	class WHALE_API FResult
	{
	public:
		
		FResult() noexcept
			: m_hr(0), m_isThrowIfFailedAtDestructTime(false) {}
		
		FResult(Win32::HResult hr) noexcept// NOLINT(*-explicit-constructor)
			: m_hr(hr), m_isThrowIfFailedAtDestructTime(true) {}
		
		FResult(const FResult &other) noexcept
			: m_hr(other.m_hr), m_isThrowIfFailedAtDestructTime(other.m_isThrowIfFailedAtDestructTime) {}
		
		FResult(FResult &&other) noexcept
			: FResult() { Swap(other); }
		
		~FResult();
	
	public:
		
		FResult &operator=(const FResult &other) noexcept
		{
			FResult(other).Swap(*this);
			return *this;
		}
		
		FResult &operator=(FResult &&other) noexcept
		{
			FResult(Whale::Move(other)).Swap(*this);
			return *this;
		}
		
		FResult &operator=(Win32::HResult hr) noexcept
		{
			this->m_hr = hr;
			return *this;
		}
	
	public:
		
		///
		/// \param message
		/// \return 字符串
		[[nodiscard]]
		StringA ToString(const StringA &message) const;
		
		[[nodiscard]]
		StringW ToString(const StringW &message) const;
		
		///
		/// 输出到日志并抛异常
		void Throw(const StringA &message, const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
		void Throw(const StringW &message, const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
		///
		/// \return 是否是失败值
		[[nodiscard]]
		Bool IsFailed() const;
		
		///
		/// \return 是否是成功值
		[[nodiscard]]
		Bool IsSucceeded() const;
		
		///
		/// 如果失败则调用Throw()
		void ThrowIfFailed(const StringA &message,
		                   const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
		void ThrowIfFailed(const StringW &message,
		                   const FSourceLocation &sourceLocation = FSourceLocation::Current());
	
	public:
		
		void Swap(FResult &other) noexcept
		{
			Whale::Swap(m_hr, other.m_hr);
			Whale::Swap(m_isThrowIfFailedAtDestructTime, other.m_isThrowIfFailedAtDestructTime);
		}
	
	public:
		
		[[nodiscard]]Win32::HResult GetHr() const noexcept { return this->m_hr; }
		
		[[nodiscard]]Bool
		IsThrowIfFailedAtDestructTime() const noexcept { return this->m_isThrowIfFailedAtDestructTime; }
		
		void SetIsThrowIfFailedAtDestructTime(Bool arg) noexcept
		{
			this->m_isThrowIfFailedAtDestructTime = arg;
		}
	
	private:
		
		Win32::HResult m_hr;
		
		Bool m_isThrowIfFailedAtDestructTime;
		
	};
	
} // Whale
