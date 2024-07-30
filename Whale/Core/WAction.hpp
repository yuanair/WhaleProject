//
// Created by admin on 2024/7/30.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"
#include "Whale/Core/WObject.hpp"
#include "TFEvent.hpp"

namespace Whale
{
	
	/// 行动函数参数
	struct WHALE_API ActionEventArg
	{
	
	};
	
	/// 行动函数类型
	using ActionEvent = TFEvent<const ActionEventArg &>;
	
	/// 行动
	class WHALE_API WAction : public WObject
	{
	public:
		
		ActionEvent triggered;
		
		ActionEvent started;
		
		ActionEvent ongoing;
		
		ActionEvent canceled;
		
		ActionEvent completed;
		
	};
	
} // Whale
