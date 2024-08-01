//
// Created by admin on 2024/7/30.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/WObject.hpp>
#include "WInputSystem.hpp"

#include "Win32/HWinDef.hpp"

#include <Eigen/Core>

namespace Whale
{
	
	/// 窗口
	class WHALE_API WWindow : public WObject
	{
	public:
		
		///
		virtual void ShowAndUpdate() = 0;
		
		///
		virtual void Tick(Float deltaTime) = 0;
		
		/// 开启文件拖放
		virtual Bool EnableFileDrag() = 0;
		
		/// 窗口矩形
		[[nodiscard]]
		virtual Eigen::Vector4i GetRect() const = 0;
		
		/// 设置窗口矩形
		virtual void SetRect(const Eigen::Vector4i &rect) = 0;
		
		/// 窗口句柄
		[[nodiscard]]
		virtual const Win32::HWindow &GetHWindow() const noexcept = 0;
	
	public:
		
		/// 输入系统
		WInputSystem m_inputSystem;
		
	};
	
} // Whale
