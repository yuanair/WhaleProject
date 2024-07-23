//
// Created by admin on 2024/7/9.
//

#pragma once

#include "Whale/Core/WObject.hpp"
#include "Whale/Platform/Win32/WWindow.hpp"
#include "Whale/Core/Memory.hpp"
#include "Whale/Core/Container/TFArray.hpp"
#include "WRenderObject.hpp"

namespace Whale
{
	///
	/// 渲染目标
	class WHALE_API WRenderTarget : public WObject
	{
	public:
		
		virtual void OnRender() = 0;
	
	public:
		
		Container::TFArray<TFWeakPtr<WRenderObject>> renderObjects;
		
	};
	
	///
	/// 窗口渲染目标
	class WHALE_API WWindowRenderTarget : public WRenderTarget
	{
	public:
		
		///
		/// 创建
		/// \param window 渲染窗口
		virtual void Create(const Win32::WWindow &window) = 0;
		
	};
	
	
} // Whale
