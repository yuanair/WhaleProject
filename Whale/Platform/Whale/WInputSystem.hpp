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
	
	/// 鼠标按键类型
	enum EMouseButtonType : uint64
	{
		EMouseButtonNone = 0,
		EMouseButtonLeft,
		EMouseButtonMiddle,
		EMouseButtonRight
	};
	
	/// 键盘按键
	enum EKeyType : uint64
	{
		EKeyNone = 0,
		EKeyA    = 'A',
		EKeyZ    = 'Z'
	};
	
	/// 按钮
	class WHALE_API WButton : public WObject
	{
	public:
		
		WButton();
		
		~WButton() override = default;
	
	public:
		
		/// 按下
		void Press();
		
		/// 释放
		void Release();
		
		/// 调用Press|Release之前调用，重置m_started&m_completed为false。
		void Tick();
	
	public:
		
		/// 是否按下了
		[[nodiscard]] Bool IsTriggered() const { return m_triggered; }
		
		/// 当前是否按下
		[[nodiscard]] Bool IsStarted() const { return m_started; }
		
		/// 当前是否释放
		[[nodiscard]] Bool IsCompleted() const { return m_completed; }
	
	private:
		
		Bool m_triggered;
		Bool m_started;
		Bool m_completed;
		
	};
	
	/// 鼠标按键
	class WHALE_API WMouseButton : public WButton
	{
	public:
		
		WMouseButton();
		
		explicit WMouseButton(EMouseButtonType type);
		
		~WMouseButton() override = default;
	
	public:
		
		/// 获取类型
		[[nodiscard]] EMouseButtonType GetType() const { return m_type; }
	
	private:
		
		EMouseButtonType m_type;
		
	};
	
	/// 键盘按键
	class WHALE_API WKey : public WButton
	{
	public:
		
		WKey();
		
		explicit WKey(EKeyType type);
		
		~WKey() override = default;
	
	public:
		
		/// 获取类型
		[[nodiscard]] EKeyType GetType() const { return m_type; }
	
	private:
		
		EKeyType m_type;
		
	};
	
	/// 输入系统
	class WHALE_API WInputSystem : public WObject
	{
	public:
		
		void Tick();
		
		void PressCloseButton();
		
		void ReleaseCloseButton();
		
		void PressKey(EKeyType type1);
		
		void ReleaseKey(EKeyType type1);
		
		void PressMouseButton(EMouseButtonType type1);
		
		void ReleaseMouseButton(EMouseButtonType type1);
		
		[[nodiscard]] const WKey *GetKey(EKeyType type1) const;
		
		[[nodiscard]] const WMouseButton *GetMouseButton(EMouseButtonType type1) const;
	
	public:
		
		[[nodiscard]] inline auto &GetCloseButton() const { return m_closeButton; }
		
		[[nodiscard]] inline auto &GetMouses() const { return m_mouseButtons; }
		
		[[nodiscard]] inline auto &GetKeys() const { return m_keys; }
	
	public:
		
		TFEvent<class WGenericWindow *> onCreate;
		
		WAction onResize;
		
		TFEvent<class WGenericWindow *> onClose;
		
		TFEvent<class WGenericWindow *> onDestroy;
		
		TFEvent<HDrop> onDrop;
	
	private:
		
		WButton m_closeButton;
		
		Container::TFArray<WMouseButton> m_mouseButtons;
		
		Container::TFArray<WKey> m_keys;
		
	};
	
} // Whale
