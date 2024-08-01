//
// Created by admin on 2024/7/30.
//

#pragma once

#include "TypeDef.hpp"
#include "WObject.hpp"
#include "TFEvent.hpp"

namespace Whale
{
	
	struct WHALE_API ActionEventValue
	{
		int32 x = 0;
		int32 y = 0;
		int32 z = 0;
		int32 w = 0;
	};
	
	/// 行动函数参数
	struct WHALE_API ActionEventArg
	{
		ActionEventValue &value;
		Float            pressedTime = 0.0f;
	};
	
	/// 行动函数类型
	using ActionEvent = TFEvent<const ActionEventArg &>;
	
	/// 行动
	class WHALE_API WAction : public WObject
	{
	public:
		
		WAction() : m_isDown(false), m_pressedTime(0.0f) {}
	
	public:
		
		inline void Tick(Float deltaTime, ActionEventValue value)
		{
			m_isDown = true;
			m_pressedTime += deltaTime;
			started.Call({.value=value, .pressedTime=m_pressedTime});
		}
		
		inline void Press(ActionEventValue value)
		{
			m_isDown      = true;
			m_pressedTime = 0.0f;
			started.Call({.value=value, .pressedTime=m_pressedTime});
		}
		
		inline void Canceled(ActionEventValue value)
		{
			m_isDown = false;
			canceled.Call({.value=value, .pressedTime=m_pressedTime});
		}
		
		inline void Release(ActionEventValue value)
		{
			m_isDown = false;
			completed.Call({.value=value, .pressedTime=m_pressedTime});
		}
	
	public:
		
		ActionEvent triggered;
		
		ActionEvent started;
		
		ActionEvent ongoing;
		
		ActionEvent canceled;
		
		ActionEvent completed;
	
	private:
		
		Bool m_isDown;
		
		Float m_pressedTime;
		
	};
	
} // Whale
