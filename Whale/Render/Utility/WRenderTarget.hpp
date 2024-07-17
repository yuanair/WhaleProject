//
// Created by admin on 2024/7/9.
//

#pragma once

#include <vector>

#include "Whale/Core/Object/WObject.hpp"
#include "Whale/Render/Win32/WWindow.hpp"
#include "Whale/Core/Container/FMemory.hpp"
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
		
		std::vector<FTWeakPtr<WRenderObject>> renderObjects;
		
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
