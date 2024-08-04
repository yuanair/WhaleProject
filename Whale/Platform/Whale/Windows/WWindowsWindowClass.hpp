//
// Created by admin on 2024/8/2.
//

#pragma once

#include "HWinDef.hpp"
#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>

#include "../WGenericWindowClass.hpp"

namespace Whale
{
	
	class WHALE_API WWindowsWindowClass : public WGenericWindowClass
	{
	public:
		
		static constexpr Char logTag[] = WTEXT("WhalePlatform::WWindowsWindowClass");
	
	public:
		
		Bool Create(const FWindowClassCreateArg &arg) override;
	
	public:
		
		Bool Create(const FWindowClassCreateArg &arg, HInstance hInstance, HIcon icon, HIcon iconSm);
	
	private:
		
		HInstance m_hInstance;
		
	};
	
} // Whale
