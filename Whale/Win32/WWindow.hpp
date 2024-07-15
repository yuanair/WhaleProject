//
// Created by admin on 2024/7/1.
//

#pragma once

#include "FWinDef.hpp"
#include "FCore.hpp"
#include "Whale/Core/WObject.hpp"
#include "Whale/Core/FTString.hpp"

namespace Whale::Win32
{
	// 窗口
	class WHALE_API WWindow : public WObject
	{
	public:
		
		// 窗口类
		class WHALE_API WWindowClass : public WObject
		{
		public:
			
			
			explicit WWindowClass(const HInstance &hInstance, FTStringT name);
			
			~WWindowClass() override;
		
		public:
			
			// 注册窗口类
			Bool Register(HIcon hIcon = {}, HIcon hIconSm = {});
			
			// 取消注册
			Bool Unregister();
			
			// 获取窗口类名
			[[nodiscard]]
			const FTStringT &GetName() const;
			
			// 获取应用实例
			[[nodiscard]]
			const HInstance &GetHInstance() const;
		
		private:
			
			const HInstance hInstance;
			
			const FTStringT name;
			
		};
		
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
		
		WWindow();
		
		~WWindow() override;
	
	public:
		
		static int64 DefaultWindowProc(HWindow hWnd, uint32 msg, uint64 wParam, uint64 lParam);
		
		///
		/// \return 桌面窗口
		static HWindow DesktopWindow();
	
	public:
		
		// 创建窗口
		void Create(
			const WWindowClass &windowClass, const FTStringT &windowName,
			int32 x = INT_MIN, int32 y = INT_MIN, int32 w = INT_MIN, int32 h = INT_MIN, HWindow hWndParent = {}
		);
		
		///
		/// 绑定句柄
		/// \param pHwnd 窗口句柄
		void Bind(HWindow pHwnd) noexcept;
		
		///
		/// 第一次显示窗口时调用
		///
		/// \param nCmdShow 可传入WinMain的参数nShowCmd。否则，传入SW_SHOW
		inline void ShowAndUpdate() const noexcept
		{
			Show(Win32::FCore::GetCommandShow());
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
		
		///
		/// 销毁窗口
		void Destroy() const;
		
		///
		/// \param deltaTime
		inline void Tick(float deltaTime)
		{
			OnTick(deltaTime);
		}
	
	protected:
		
		///
		/// 按下按键事件
		///
		/// \param args 参数
		virtual uint64 OnKeyDown(const EventKeyArgs &args) { return 0; }
		
		///
		/// 松开按键事件
		///
		/// \param args 参数
		virtual uint64 OnKeyUp(const EventKeyArgs &args) { return 0; }
		
		///
		/// 鼠标移动事件
		///
		/// \param args 参数
		virtual uint64 OnMouseMoved(const EventOnMouseMoveArgs &args) { return 0; }
		
		///
		/// 窗口移动事件
		///
		/// \param args 参数
		virtual uint64 OnMove(const EventOnMoveArgs &args) { return 0; }
		
		///
		/// 创建窗口事件
		///
		/// \param args 参数
		virtual uint64 OnCreate() { return 0; }
		
		///
		/// 窗口大小改变事件
		///
		/// \param args 参数
		virtual uint64 OnResize(const EventOnResizeArgs &args) { return 0; }
		
		///
		/// 输入字符事件
		///
		/// \param input 输入的字符
		virtual uint64 OnChar(const TChar &input) { return 0; }
		
		///
		/// 输入字符串事件，用于输入法
		///
		/// \param input 输入的字符串
		virtual uint64 OnString(const FTStringT &input) { return 0; }
		
		///
		/// Tick事件
		///
		/// \param deltaTIme 间隔时间
		virtual void OnTick(float deltaTIme) {}
		
		///
		/// 活动事件
		///
		virtual uint64 OnInactive() { return 0; }
		
		///
		/// 窗口活动事件
		///
		virtual uint64 OnActive() { return 0; }
		
		///
		/// 点击窗口使其活动事件
		///
		virtual uint64 OnClickActive() { return 0; }
		
		///
		/// 拖放文件到窗口事件
		///
		/// \param hDropInfo 拖放的文件
		virtual uint64 OnDropFiles(HDrop hDropInfo) { return 0; };
		
		///
		/// 关闭事件
		///
		virtual uint64 OnClose()
		{
			Destroy();
			return 0;
		}
		
		///
		/// 销毁事件
		///
		virtual uint64 OnDestroy() { return 0; }
		
		///
		/// 询问关机事件
		///
		/// \return 是否可以关机
		virtual uint64 OnQueryEndSession() { return true; }
		
		///
		/// 关机事件
		///
		/// \return 是否可以关机
		virtual uint64 OnEndSession() { return true; }
	
	public:
		
		///
		/// \return 窗口名
		[[nodiscard]]
		std::string GetNameA() const;
		
		///
		/// \return 窗口名
		[[nodiscard]]
		std::wstring GetNameW() const;
		
		///
		/// \param name 窗口名
		void SetName(const std::string &name);
		
		///
		/// \param name 窗口名
		void SetName(const std::wstring &name);
		
		///
		/// \return 窗口矩形
		[[nodiscard]]
		FRectI GetRect() const;
		
		///
		/// \param rect 窗口矩形
		void SetRect(const FRectI &rect);
		
		///
		/// \return 窗口句柄
		[[nodiscard]]
		inline const HWindow &GetHWindow() const noexcept { return this->hWindow; }
	
	private:
		
		static uint64 WindowProc(void *hWnd, uint32 msg, uint64 wParam, int64 lParam);
		
		uint64 OnMessage(uint32 msg, uint64 wParam, int64 lParam);
	
	protected:
		
		///
		/// 是否启用OnChar事件
		///
		Bool bEnableOnChar = false;
		
		///
		/// 是否启用OnString事件
		///
		Bool bEnableOnString = false;
		
		///
		/// 输入位置，用于输入法定位
		///
		FPoint2I inputPoint;
		
		///
		/// 鼠标光标
		HCursor hCursor;
		
		///
		/// 窗口最小大小
		FSize2I minSize;
		
		///
		/// 窗口最大大小
		FSize2I maxSize;
	
	private:
		
		HWindow hWindow;
		
		FPoint2I mousePosition;
		
	};
	
} // Whale
