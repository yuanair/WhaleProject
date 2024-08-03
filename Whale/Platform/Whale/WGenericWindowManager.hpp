//
// Created by admin on 2024/8/3.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>
#include "WGenericWindow.hpp"

namespace Whale
{
	
	/// 窗口管理器
	class WHALE_API WGenericWindowManager : public WObject
	{
	public:
		
		WGenericWindowManager() = default;
		
		WGenericWindowManager(const WGenericWindowManager &) = delete;
	
	public:
		
		WGenericWindowManager &operator=(const WGenericWindowManager &) = delete;
	
	public:
		
		/// 新建窗口类
		virtual WGenericWindowClass *NewWindowClass() = 0;
		
		/// 删除窗口类
		virtual void DeleteWindowClass(WGenericWindowClass *windowClass) = 0;
		
		/// 新建窗口
		virtual WGenericWindow *NewWindow() = 0;
		
		/// 删除窗口
		virtual void DeleteWindow(WGenericWindow *window) = 0;
		
	};
	
} // Whale
