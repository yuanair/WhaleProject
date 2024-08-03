//
// Created by admin on 2024/8/3.
//

#include "WWindowsWindowManager.hpp"

#include "WWindowsWindow.hpp"
#include "WWindowsWindowClass.hpp"

namespace Whale
{
	WWindowsWindowManager &WWindowsWindowManager::Get()
	{
		static WWindowsWindowManager windowManager;
		return windowManager;
	}
	
	WGenericWindowClass *WWindowsWindowManager::NewWindowClass()
	{
		return m_pWindowClasses.Emplace(MakeUnique<WWindowsWindowClass>()).GetPtr();
	}
	
	void WWindowsWindowManager::DeleteWindowClass(WGenericWindowClass *windowClass)
	{
		for (SizeT index = 0; index < m_pWindowClasses.GetLength();)
		{
			if (windowClass == m_pWindowClasses[index].GetPtr())
			{
				m_pWindowClasses.Erase(index);
				continue;
			}
			index++;
		}
	}
	
	WGenericWindow *WWindowsWindowManager::NewWindow()
	{
		return m_pWindows.Emplace(MakeUnique<WWindowsWindow>()).GetPtr();
	}
	
	void WWindowsWindowManager::DeleteWindow(WGenericWindow *window)
	{
		for (SizeT index = 0; index < m_pWindows.GetLength();)
		{
			if (window == m_pWindows[index].GetPtr())
			{
				m_pWindows.Erase(index);
				continue;
			}
			index++;
		}
	}
} // Whale