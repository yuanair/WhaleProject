//
// Created by admin on 2024/7/6.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/Container/TFString.hpp>
#include <Whale/SourceLocation.hpp>
#include <Whale/Exception.hpp>
#include "HWinDef.hpp"

namespace Whale
{
	
	class FResultException : public FException
	{
	public:
		
		FResultException()
			: FException() {}
		
		explicit FResultException(const Char *message)
			: FException(message) {}
		
	};
	
	class WHALE_API FResult
	{
	public:
		
		FResult() noexcept
			: m_hr(0), m_isThrowIfFailedAtDestructTime(false) {}
		
		FResult(HResult hr) noexcept// NOLINT(*-explicit-constructor)
			: m_hr(hr), m_isThrowIfFailedAtDestructTime(true) {}
		
		FResult(const FResult &other) noexcept
			: m_hr(other.m_hr), m_isThrowIfFailedAtDestructTime(other.m_isThrowIfFailedAtDestructTime) {}
		
		FResult(FResult &&other) noexcept
			: FResult() { Swap(other); }
		
		~FResult();
	
	public:
		
		static constexpr Char  logTag[]  = WTEXT("WhalePlatform::FResult");
		static constexpr CharA logTagA[] = "WhalePlatform::FResult";
		static constexpr CharW logTagW[] = L"WhalePlatform::FResult";
	
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
		
		FResult &operator=(HResult hr) noexcept
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
		/// 输出到日志
		void Log(const StringA &message, const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
		void Log(const StringW &message, const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
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
		
		///
		/// 如果失败则调用Log()
		void LogIfFailed(const StringA &message,
		                 const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
		void LogIfFailed(const StringW &message,
		                 const FSourceLocation &sourceLocation = FSourceLocation::Current());
	
	public:
		
		void Swap(FResult &other) noexcept
		{
			Whale::Swap(m_hr, other.m_hr);
			Whale::Swap(m_isThrowIfFailedAtDestructTime, other.m_isThrowIfFailedAtDestructTime);
		}
	
	public:
		
		[[nodiscard]]HResult GetHr() const noexcept { return this->m_hr; }
		
		[[nodiscard]]Bool
		IsThrowIfFailedAtDestructTime() const noexcept { return this->m_isThrowIfFailedAtDestructTime; }
		
		void SetIsThrowIfFailedAtDestructTime(Bool arg) noexcept
		{
			this->m_isThrowIfFailedAtDestructTime = arg;
		}
	
	private:
		
		HResult m_hr;
		
		Bool m_isThrowIfFailedAtDestructTime;
		
	};
	
} // Whale
