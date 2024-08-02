//
// Created by admin on 2024/7/31.
//

#pragma once

#include "TFFunction.hpp"
#include "Container/TFArray.hpp"

namespace Whale
{
	
	/// 事件
	template<class... Args>
	class WHALE_API TFEvent
	{
	public:
		
		using FunctionType = TFFunction<void, Args...>;
	
	public:
		
		inline TFEvent &operator+=(FunctionType function) noexcept
		{
			m_functions.Append(function);
			return *this;
		}
	
	public:
		
		inline void Call(Args... args) noexcept
		{
			for (auto &function: m_functions)
			{
				if (function) function(Whale::Forward<Args>(args)...);
			}
		}
	
	private:
		
		Container::TFArray<FunctionType> m_functions;
		
	};
	
} // Whale
