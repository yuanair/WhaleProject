//
// Created by admin on 2024/8/4.
//

#pragma once

#include "HWinDef.hpp"

#include "../WGenericTime.hpp"

namespace Whale
{
	
	class WHALE_API WWindowsTime : public WGenericTime
	{
	public:
		
		static WWindowsTime &Get();
	
	public:
		
		void GetSystemTime(FTime &time) const override;
		
		void GetLocalTime(FTime &time) const override;
	
	private:
		
		WWindowsTime() = default;
		
	};
	
} // Whale
