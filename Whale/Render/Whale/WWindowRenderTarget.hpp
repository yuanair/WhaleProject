//
// Created by admin on 2024/7/25.
//

#pragma once

#include "WRenderTarget.hpp"
#include <Whale/WGenericWindow.hpp>

namespace Whale
{
	
	///
	/// 参数
	struct WHALE_API FWRTCreateArg
	{
		
		/// 渲染窗口
		const WGenericWindow &m_window;
		
		/// 缓冲区数量
		uint32 m_frameBackBufferCount = 2;
		
	};
	
	///
	/// 窗口渲染目标
	class WHALE_API WWindowRenderTarget : public WRenderTarget
	{
	public:
		
		///
		/// 创建
		virtual void Create(const FWRTCreateArg &arg) = 0;
		
	};
	
} // Whale
