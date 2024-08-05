//
// Created by admin on 2024/7/30.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>
#include "Windows/HWinDef.hpp"
#include "WGenericWindowClass.hpp"
#include "WInputSystem.hpp"

#include <Eigen/Core>

namespace Whale
{
	
	/// 创建窗口参数
	struct WHALE_API FWindowCreateArg
	{
		/// 窗口名
		FString             m_name;
		/// 窗口类
		WGenericWindowClass *m_class = nullptr;
		/// 窗口x坐标
		int32               m_x      = INT_MIN;
		/// 窗口y坐标
		int32               m_y      = INT_MIN;
		/// 窗口宽度
		int32               m_width  = INT_MIN;
		/// 窗口高度
		int32               m_height = INT_MIN;
	};
	
	/// 窗口
	class WHALE_API WGenericWindow : public WObject
	{
	public:
		
		WGenericWindow() = default;
	
	public:
		
		/// 创建窗口
		virtual void Create(const FWindowCreateArg &arg) = 0;
		
		/// 显示窗口
		virtual void ShowAndUpdate() = 0;
		
		/// 开启文件拖放
		virtual Bool EnableFileDrag() = 0;
		
		/// 消息处理
		virtual void MessageHanding() = 0;
	
	public:
		
		/// 窗口矩形
		[[nodiscard]]
		virtual Eigen::Vector4i GetRect() const = 0;
		
		/// 设置窗口矩形
		virtual void SetRect(const Eigen::Vector4i &rect) = 0;
	
	public:
		
		virtual LResult OnMessage(UInt msg, WParam wParam, LParam lParam) = 0;
		
		[[nodiscard]] virtual HWindow GetHWindow() const noexcept = 0;
	
	public:
		
		/// 输入系统
		WInputSystem m_inputSystem;
		
	};
	
} // Whale
