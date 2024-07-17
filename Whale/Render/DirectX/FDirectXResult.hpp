//
// Created by admin on 2024/7/6.
//

#pragma once

#include "Whale/Core/Tool/FTypeDef.hpp"
#include "Whale/Core/Container/FTString.hpp"
#include "Whale/Core/Tool/FSourceLocation.hpp"
#include "Whale/Core/FException/FException.hpp"

namespace Whale
{
	
	class FDirectXResultException : public FException
	{
	public:
		
		FDirectXResultException()
			: FException() {}
		
		explicit FDirectXResultException(const Char *message)
			: FException(message) {}
		
	};
	
	///
	/// HResult
	class WHALE_API FDirectXResult
	{
	public:
		
		FDirectXResult(int32 hr); // NOLINT(*-explicit-constructor)
		
		~FDirectXResult();
	
	public:
		
		///
		/// \param message
		/// \return 字符串
		[[nodiscard]]
		FTStringA ToString(const FTStringA &message) const;
		
		[[nodiscard]]
		FTStringW ToString(const FTStringW &message) const;
		
		///
		/// 输出到日志并抛异常
		void Throw(const FTStringA &message, const FSourceLocation &sourceLocation = FSourceLocation::Current()) const;
		
		void Throw(const FTStringW &message, const FSourceLocation &sourceLocation = FSourceLocation::Current()) const;
		
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
		void ThrowIfFailed(const FTStringA &message,
		                   const FSourceLocation &sourceLocation = FSourceLocation::Current()) const;
		
		void ThrowIfFailed(const FTStringW &message,
		                   const FSourceLocation &sourceLocation = FSourceLocation::Current()) const;
	
	public:
		
		[[nodiscard]]
		int32 GetHr() const;
		
		[[nodiscard]]
		bool IsThrowIfFailedAtDestructTime() const;
		
		void SetIsThrowIfFailedAtDestructTime(bool isThrowIfFailedAtDestructTime);
	
	private:
		
		const int32 hr;
		
		bool isThrowIfFailedAtDestructTime = true;
		
	};
	
} // Whale
