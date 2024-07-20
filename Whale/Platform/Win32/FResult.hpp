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
	
	///
	/// HResult
	class WHALE_API FResult
	{
	public:
		
		FResult(Win32::HResult hr) : hr(hr),
		                             isThrowIfFailedAtDestructTime(true) {} // NOLINT(*-explicit-constructor)
		
		~FResult();
	
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
		void Throw(const StringA &message, const FSourceLocation &sourceLocation = FSourceLocation::Current()) const;
		
		void Throw(const StringW &message, const FSourceLocation &sourceLocation = FSourceLocation::Current()) const;
		
		///
		/// \return 是否是失败值
		[[nodiscard]]
		bool IsFailed() const;
		
		///
		/// \return 是否是成功值
		[[nodiscard]]
		bool IsSucceeded() const;
		
		///
		/// 如果失败则调用Throw()
		void ThrowIfFailed(const StringA &message,
		                   const FSourceLocation &sourceLocation = FSourceLocation::Current()) const;
		
		void ThrowIfFailed(const StringW &message,
		                   const FSourceLocation &sourceLocation = FSourceLocation::Current()) const;
	
	public:
		
		[[nodiscard]]
		Win32::HResult GetHr() const { return this->hr; }
		
		[[nodiscard]]
		bool IsThrowIfFailedAtDestructTime() const { return this->isThrowIfFailedAtDestructTime; }
		
		void SetIsThrowIfFailedAtDestructTime(bool arg)
		{
			this->isThrowIfFailedAtDestructTime = arg;
		}
	
	private:
		
		const Win32::HResult hr;
		
		bool isThrowIfFailedAtDestructTime;
		
	};
	
} // Whale
