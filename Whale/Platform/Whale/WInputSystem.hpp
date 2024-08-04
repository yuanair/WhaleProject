//
// Created by admin on 2024/7/30.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/WObject.hpp>
#include <Whale/WAction.hpp>
#include "Whale/Windows/HWinDef.hpp"

namespace Whale
{
	
	/// 输入系统
	class WHALE_API WInputSystem : public WObject
	{
	public:
		
		TFEvent<class WGenericWindow *> onCreate;
		
		WAction onResize;
		
		WAction onKey;
		
		TFEvent<class WGenericWindow *> onClose;
		
		TFEvent<class WGenericWindow *> onDestroy;
		
		TFEvent<HDrop> onDrop;
		
	};
	
} // Whale
