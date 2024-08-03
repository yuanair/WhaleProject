//
// Created by admin on 2024/8/3.
//

#pragma once

#include "HWinDef.hpp"
#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>

#include "../WGenericWindowManager.hpp"

namespace Whale
{
	
	class WHALE_API WWindowsWindowManager : public WGenericWindowManager
	{
	public:
		
		static WWindowsWindowManager &Get();
	
	public:
		
		WGenericWindowClass *NewWindowClass() override;
		
		void DeleteWindowClass(WGenericWindowClass *windowClass) override;
		
		WGenericWindow *NewWindow() override;
		
		void DeleteWindow(WGenericWindow *window) override;
	
	private:
		
		WWindowsWindowManager() = default;
	
	private:
		
		Container::TFArray<TFUniquePtr<WGenericWindowClass>> m_pWindowClasses;
		
		Container::TFArray<TFUniquePtr<WGenericWindow>> m_pWindows;
		
	};
	
} // Whale
