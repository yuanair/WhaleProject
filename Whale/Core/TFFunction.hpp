//
// Created by admin on 2024/7/30.
//

#pragma once

#include "TypeDef.hpp"
#include "Utility.hpp"

namespace Whale
{
	///
	/// 函数指针
	/// \tparam Result
	/// \tparam Args
	template<class Result, class... Args>
	class WHALE_API TFFunction
	{
	public:
		
		using ResultT = Result;
		using FunctionType = Result (*)(Args... args);
	
	public:
		
		TFFunction() : m_function(nullptr) {}
		
		TFFunction(NullPtrT) : m_function(nullptr) {} // NOLINT(*-explicit-constructor)
		
		TFFunction(FunctionType function) : m_function(function) {} // NOLINT(*-explicit-constructor)
	
	public:
		
		inline explicit operator Bool() const noexcept { return m_function != nullptr; }
		
		inline Result operator()(Args ... args) const
		{
			return m_function(Whale::Forward<Args>(args)...);
		}
	
	public:
		
		inline Result Call(Args ... args) const
		{
			return m_function(Whale::Forward<Args>(args)...);
		}
	
	public:
		
		auto GetFunction() const noexcept { return m_function; }
		
		void SetFunction(FunctionType function) noexcept { m_function = function; }
	
	private:
		
		FunctionType m_function;
		
	};
	
} // Whale
