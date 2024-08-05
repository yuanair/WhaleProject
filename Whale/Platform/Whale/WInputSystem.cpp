//
// Created by admin on 2024/7/30.
//

#include "WInputSystem.hpp"

namespace Whale
{
	WButton::WButton()
		: m_triggered(false), m_started(false), m_completed(false)
	{
	
	}
	
	void WButton::Press()
	{
		m_triggered = true;
		m_started   = true;
	}
	
	void WButton::Release()
	{
		m_triggered = false;
		m_completed = true;
	}
	
	void WButton::Tick()
	{
		m_started   = false;
		m_completed = false;
	}
	
	WMouseButton::WMouseButton()
		: m_type(EMouseButtonNone)
	{
	
	}
	
	WMouseButton::WMouseButton(EMouseButtonType type) : m_type(type) {}
	
	WKey::WKey()
		: m_type(EKeyNone)
	{
	
	}
	
	WKey::WKey(EKeyType type) : m_type(type) {}
	
	void WInputSystem::Tick()
	{
		m_closeButton.Tick();
		for (auto &item: m_keys)
		{
			item.Tick();
		}
		for (auto &item: m_mouseButtons)
		{
			item.Tick();
		}
	}
	
	void WInputSystem::PressCloseButton()
	{
		m_closeButton.Press();
	}
	
	void WInputSystem::ReleaseCloseButton()
	{
		m_closeButton.Release();
	}
	
	void WInputSystem::PressKey(EKeyType type1)
	{
		for (SizeT index = 0; index < m_keys.GetLength(); index++)
		{
			if (m_keys[index].GetType() == type1)
			{
				m_keys[index].Press();
				return;
			}
		}
		m_keys.Emplace(type1).Press();
	}
	
	void WInputSystem::ReleaseKey(EKeyType type1)
	{
		for (SizeT index = 0; index < m_keys.GetLength(); index++)
		{
			if (m_keys[index].GetType() == type1)
			{
				m_keys[index].Release();
				return;
			}
		}
		m_keys.Emplace(type1).Release();
	}
	
	void WInputSystem::PressMouseButton(EMouseButtonType type1)
	{
		for (SizeT index = 0; index < m_mouseButtons.GetLength(); index++)
		{
			if (m_mouseButtons[index].GetType() == type1)
			{
				m_mouseButtons[index].Press();
				return;
			}
		}
		m_mouseButtons.Emplace(type1).Press();
	}
	
	void WInputSystem::ReleaseMouseButton(EMouseButtonType type1)
	{
		for (SizeT index = 0; index < m_mouseButtons.GetLength(); index++)
		{
			if (m_mouseButtons[index].GetType() == type1)
			{
				m_mouseButtons[index].Release();
				return;
			}
		}
		m_mouseButtons.Emplace(type1).Release();
	}
	
	const WKey *WInputSystem::GetKey(EKeyType type1) const
	{
		for (auto &item: m_keys)
		{
			if (item.GetType() == type1) return &item;
		}
		return nullptr;
	}
	
	const WMouseButton *WInputSystem::GetMouseButton(EMouseButtonType type1) const
	{
		for (auto &item: m_mouseButtons)
		{
			if (item.GetType() == type1) return &item;
		}
		return nullptr;
	}
} // Whale