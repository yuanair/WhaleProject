//
// Created by admin on 2024/7/1.
//

#pragma once

#include "HWinDef.hpp"
#include "FCore.hpp"
#include "Whale/WObject.hpp"
#include <Whale/Container/TFString.hpp>
#include <Whale/WGenericWindow.hpp>

#include <Eigen/Core>

namespace Whale
{
	// 窗口
	class WHALE_API WWindowsWindow : public WGenericWindow
	{
	public:
		
		friend class WWindowsWindowClass;
	
	public:
		
		
		///
		/// 按键事件参数
		///
		struct EventKeyArgs
		{
			///
			/// 虚拟按键。例如VK_BACK
			///
			uint64 virtualKey;
			
		};
		
		///
		/// 鼠标移动事件参数
		///
		struct EventOnMouseMoveArgs
		{
			
			//
			// 鼠标x坐标
			//
			int32 mouseX;
			
			//
			// 鼠标y坐标
			//
			int32 mouseY;
			
			//
			// 鼠标x坐标偏移
			//
			int32 deltaX;
			
			//
			// 鼠标y坐标偏移
			//
			int32 deltaY;
			
		};
		
		//
		// 改变大小事件参数
		//
		struct EventOnMoveArgs
		{
			
			//
			// 窗口x坐标
			//
			int32 x;
			
			//
			// 窗口y坐标
			//
			int32 y;
		};
		
		//
		// 改变大小事件参数
		//
		struct EventOnResizeArgs
		{
			
			//
			// 窗口宽度
			//
			int32 width;
			
			//
			// 窗口高度
			//
			int32 height;
		};
	
	public:
		
		WWindowsWindow();
		
		~WWindowsWindow() override;
	
	public:
		
		static constexpr Char logTag[] = WTEXT("WhalePlatform::WWindowsWindow");
	
	public:
		
		static LResult DefaultWindowProc(HWindow hWnd, UInt msg, WParam wParam, LParam lParam);
		
		///
		/// \return 桌面窗口
		static HWindow DesktopWindow();
		
		///
		/// \return 桌面窗口大小
		static Eigen::Vector2i DesktopWindowSize();
	
	public:
		
		/// 获取文件拖放权限
		[[nodiscard]] Bool GetFileDragAndDropPermission() const noexcept;
		
		Bool EnableFileDrag() override
		{
			return GetFileDragAndDropPermission();
		}
		
		void Create(const FWindowCreateArg &arg) override;
		
		///
		/// 绑定句柄
		/// \param pHwnd 窗口句柄
		void Bind(HWindow pHwnd) noexcept;
		
		///
		/// 第一次显示窗口时调用
		///
		/// \param nCmdShow 可传入WinMain的参数nShowCmd。否则，传入SW_SHOW
		inline void ShowAndUpdate() noexcept override
		{
			Show(FCore::GetCommandShow<CharT>());
			Update();
		}
		
		///
		/// 显示窗口时调用
		///
		/// \param nCmdShow
		void Show(int32 nCmdShow) const;
		
		///
		/// 更新窗口时调用
		///
		void Update() const;
		
		void MessageHanding() override;
		
		///
		/// 销毁窗口
		void Destroy();
	
	protected:
		
		///
		/// 鼠标移动事件
		///
		/// \param args 参数
		virtual LResult OnMouseMoved(const EventOnMouseMoveArgs &args) { return 0; }
		
		///
		/// 窗口移动事件
		///
		/// \param args 参数
		virtual LResult OnMove(const EventOnMoveArgs &args) { return 0; }
		
		///
		/// 创建窗口事件
		///
		/// \param args 参数
		virtual LResult OnCreate() { return 0; }
		
		///
		/// 窗口大小改变事件
		///
		/// \param args 参数
		virtual LResult OnResize(const EventOnResizeArgs &args) { return 0; }
		
		///
		/// 输入字符事件
		///
		/// \param input 输入的字符
		virtual LResult OnChar(const CharT &input) { return 0; }
		
		///
		/// 输入字符串事件，用于输入法
		///
		/// \param input 输入的字符串
		virtual LResult OnString(const StringT &input) { return 0; }
		
		///
		/// 活动事件
		///
		virtual LResult OnInactive() { return 0; }
		
		///
		/// 窗口活动事件
		///
		virtual LResult OnActive() { return 0; }
		
		///
		/// 点击窗口使其活动事件
		///
		virtual LResult OnClickActive() { return 0; }
		
		///
		/// 拖放文件到窗口事件
		///
		/// \param hDropInfo 拖放的文件
		virtual LResult OnDropFiles(HDrop hDropInfo) { return 0; };
		
		///
		/// 销毁事件
		///
		virtual LResult OnDestroy() { return 0; }
		
		///
		/// 询问关机事件
		///
		/// \return 是否可以关机
		virtual LResult OnQueryEndSession() { return true; }
		
		///
		/// 关机事件
		///
		/// \return 是否可以关机
		virtual LResult OnEndSession() { return true; }
	
	public:
		
		///
		/// \return 窗口名
		[[nodiscard]]
		StringA GetNameA() const;
		
		///
		/// \return 窗口名
		[[nodiscard]]
		StringW GetNameW() const;
		
		///
		/// \param name 窗口名
		void SetName(const StringA &name);
		
		///
		/// \param name 窗口名
		void SetName(const StringW &name);
	
	public:
		
		[[nodiscard]]
		Eigen::Vector4i GetRect() const override;
		
		void SetRect(const Eigen::Vector4i &rect) override;
		
		[[nodiscard]]
		inline HWindow GetHWindow() const noexcept override { return this->hWindow; }
		
		LResult OnMessage(UInt msg, WParam wParam, LParam lParam) override;
	
	private:
		
		static LResult WindowProc(void *hWnd, UInt msg, WParam wParam, LParam lParam) noexcept;
	
	protected:
		
		/// 是否启用OnChar事件
		Bool bEnableOnChar   = false;
		/// 是否启用OnString事件
		Bool bEnableOnString = false;
		
		/// 输入位置，用于输入法定位
		Eigen::Vector2i inputPoint = {0, 0};
		
		/// 鼠标光标
		HCursor         hCursor       = {};
		/// 鼠标位置
		Eigen::Vector2i mousePosition = {0, 0};
		
		/// 窗口最小大小
		Eigen::Vector2i minSize = {0, 0};
		/// 窗口最大大小
		Eigen::Vector2i maxSize = {0, 0};
	
	private:
		
		HWindow hWindow;
		
	};
	
} // Whale
