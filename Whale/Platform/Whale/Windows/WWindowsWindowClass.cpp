//
// Created by admin on 2024/8/2.
//

#include "WWindowsWindowClass.hpp"
#include "WWindowsWindow.hpp"
#include "Resources.h"
#include "../FPlatformManager.hpp"

#include <Windows.h>

#undef GetModuleHandle

namespace Whale
{
	
	
	Bool WWindowsWindowClass::Create(const FWindowClassCreateArg &arg)
	{
		auto hModule = FPlatformManager::Get().GetPlatform().GetModuleHandle();
		return Create(
			arg,
			hModule,
			{
				::LoadImageW(
					static_cast<HINSTANCE>(hModule.handle), MAKEINTRESOURCEW(IDI_APP_ICON), IMAGE_ICON, 0, 0,
					LR_DEFAULTCOLOR
				)
			},
			{
				::LoadImageW(
					static_cast<HINSTANCE>(hModule.handle), MAKEINTRESOURCEW(IDI_APP_ICON_SM), IMAGE_ICON, 0, 0,
					LR_DEFAULTCOLOR
				)
			}
		);
	}
	
	Bool WWindowsWindowClass::Create(const FWindowClassCreateArg &arg, HInstance hInstance, HIcon icon, HIcon iconSm)
	{
		m_name = arg.m_name;
		m_hInstance = hInstance;
		WNDCLASSEXW wnd
			            {
				            .cbSize = sizeof(wnd),
				            .style = CS_VREDRAW | CS_HREDRAW,
				            .lpfnWndProc = reinterpret_cast<WNDPROC>(&WWindowsWindow::WindowProc),
				            .cbClsExtra = 0,
				            .cbWndExtra = sizeof(WWindowsWindow *),
				            .hInstance = static_cast<HINSTANCE>(hInstance.handle),
				            .hIcon = static_cast<HICON>(icon.handle),
				            .hCursor = nullptr,
				            .hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH),
				            .lpszMenuName = nullptr,
				            .lpszClassName = arg.m_name.CStr(),
				            .hIconSm = static_cast<HICON>(iconSm.handle),
			            };
		auto        result = ::RegisterClassExW(&wnd);
		FCore::GetLastError().LogIfFailed(logTag);
		return result;
	}
	
} // Whale