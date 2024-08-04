//
// Created by admin on 2024/7/1.
//

#pragma once

#include <Whale/TypeDef.hpp>

#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Netapi32.lib")
#pragma comment(lib, "Imm32.lib")

namespace Whale
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
	
	/// 模块
	using HModule = HInstance;
	
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
