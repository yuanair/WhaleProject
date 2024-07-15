//
// Created by admin on 2024/7/6.
//

#pragma once

#include "Whale/Core/FTypeDef.hpp"

#include <string>

namespace Whale
{
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
		std::string ToString(const std::string &message) const;
		
		[[nodiscard]]
		std::wstring ToString(const std::wstring &message) const;
		
		///
		/// 输出到日志并抛异常
		void Throw(const std::string &message) const;
		
		void Throw(const std::wstring &message) const;
		
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
		void ThrowIfFailed(const std::string &message) const;
		
		void ThrowIfFailed(const std::wstring &message) const;
	
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
