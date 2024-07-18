//
// Created by admin on 2024/7/1.
//

#pragma once

#include "Whale/Core/Tool/HTypeDef.hpp"

namespace Whale::Win32
{
	
	// 句柄
	struct HHandle
	{
	public:
		
		void *handle = nullptr;
		
	};
	
	// 窗口句柄
	struct HWindow : public HHandle {};
	
	/// 应用实例
	struct HInstance : public HHandle {};
	
	/// 图标资源
	struct HIcon : public HHandle {};
	
	/// 鼠标指针资源
	struct HCursor : public HHandle {};
	
	/// 拖放文件资源
	struct HDrop : public HHandle {};
	
	using WParam = UIntPointer;
	
	using LParam = LongPointer;
	
	using LResult = LongPointer;
	
	using HResult = Long;
	
} // Whale
