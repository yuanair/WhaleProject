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
		
		TFFunction() noexcept: m_function(nullptr) {}
		
		TFFunction(NullPtrT) noexcept: m_function(nullptr) {} // NOLINT(*-explicit-constructor)
		
		TFFunction(const TFFunction &other) noexcept: m_function(other.m_function) {}
		
		template<class T, typename = std::enable_if_t<std::negation_v<std::is_same<std::_Remove_cvref_t<T>, TFFunction>>, int>>
		TFFunction(T &&function) noexcept // NOLINT(*-explicit-constructor)
			: m_function(Whale::Forward<T>(function)) {}
		
		TFFunction(TFFunction &&other) noexcept: TFFunction() { this->Swap(other); }
	
	public:
		
		TFFunction &operator=(const TFFunction &other) noexcept
		{
			TFFunction(other).Swap(*this);
			return *this;
		}
		
		template<class T, typename = std::enable_if_t<std::negation_v<std::is_same<std::_Remove_cvref_t<T>, TFFunction>>, int>>
		TFFunction &operator=(T &&function) noexcept
		{
			TFFunction(Whale::Forward<T>(function)).Swap(*this);
			return *this;
		}
		
		TFFunction &operator=(TFFunction &&other) noexcept
		{
			TFFunction(Whale::Move(other)).Swap(*this);
			return *this;
		}
		
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
		
		inline void Swap(TFFunction &other) noexcept
		{
			Whale::Swap(m_function, other.m_function);
		}
	
	public:
		
		auto GetFunction() const noexcept { return m_function; }
		
		void SetFunction(FunctionType &&function) noexcept { m_function = function; }
	
	private:
		
		FunctionType m_function;
		
	};
	
	
} // Whale
