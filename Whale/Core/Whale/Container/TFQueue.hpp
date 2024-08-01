//
// Created by admin on 2024/8/1.
//

#pragma once

#include "../Utility.hpp"
#include "InitList.hpp"

namespace Whale::Container
{
	/// 队列
	template<class ContainerT>
	class WHALE_API TFQueue : public ContainerT
	{
	public:
		
		using ContainerT::ContainerT;
	
	public:
		
		auto Pop()
		{
			auto buffer = Whale::Move(ContainerT::operator[](0));
			ContainerT::Erase(0);
			return buffer;
		}
		
	};
	
} // Whale
