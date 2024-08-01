//
// Created by admin on 2024/7/30.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/WObject.hpp>
#include <Whale/WAction.hpp>
#include "Whale/Win32/HWinDef.hpp"

namespace Whale
{
	
	/// 输入系统
	class WHALE_API WInputSystem : public WObject
	{
	public:
		
		WAction onCreate;
		
		WAction onResize;
		
		WAction onKey;
		
		WAction onClose;
		
		WAction onDestroy;
		
		TFEvent<Win32::HDrop> onDrop;
		
	};
	
} // Whale
