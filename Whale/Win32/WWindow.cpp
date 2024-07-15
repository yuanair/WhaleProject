//
// Created by admin on 2024/7/1.
//

#include "WWindow.hpp"

#include "FCore.hpp"

#include "Whale/Core/FDebug.hpp"

#include <format>

#include <windows.h>
#include <windowsx.h>

#pragma comment(lib, "Imm32.lib")

namespace Whale::Win32
{
	
	WWindow::WWindowClass::WWindowClass(const HInstance &hInstance, FTStringT name)
		: hInstance(hInstance), name(Move(name))
	{
	
	}
	
	WWindow::WWindowClass::~WWindowClass()
	{
		Unregister();
	}
	
	bool WWindow::WWindowClass::Register(HIcon hIcon, HIcon hIconSm)
	{
		if (hIcon.handle == nullptr) hIcon.handle = ::LoadIcon(nullptr, IDI_APPLICATION);
		if (hIconSm.handle == nullptr) hIconSm.handle = ::LoadIcon(nullptr, IDI_APPLICATION);
		WNDCLASSEX wnd
			{
				.cbSize = sizeof(wnd),
				.style = CS_VREDRAW | CS_HREDRAW,
				.lpfnWndProc = (WNDPROC) (&WWindow::WindowProc),
				.cbClsExtra = 0,
				.cbWndExtra = sizeof(WWindow *),
				.hInstance = (HINSTANCE) hInstance.handle,
				.hIcon = (HICON) hIcon.handle,
				.hCursor = nullptr,
				.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH),
				.lpszMenuName = nullptr,
				.lpszClassName = name.CStr(),
				.hIconSm = (HICON) hIconSm.handle,
			};
		return ::RegisterClassEx(&wnd);
	}
	
	const FTStringT &WWindow::WWindowClass::GetName() const
	{
		return this->name;
	}
	
	Bool WWindow::WWindowClass::Unregister()
	{
		return ::UnregisterClass(this->name.CStr(), (HINSTANCE) this->hInstance.handle);
	}
	
	const HInstance &WWindow::WWindowClass::GetHInstance() const
	{
		return hInstance;
	}
	
	WWindow::WWindow()
		: inputPoint{}, hCursor{::LoadCursor(nullptr, IDC_ARROW)}
	// minSize{}, maxSize{}, mousePosition{}
	{
	
	}
	
	WWindow::~WWindow()
	{
		Destroy();
	}
	
	void WWindow::Create(
		const WWindowClass &windowClass, const FTStringT &windowName,
		int32 x, int32 y, int32 w, int32 h, HWindow hWndParent
	)
	{
		WWindow desktop;
		desktop.Bind(DesktopWindow());
		this->maxSize = desktop.GetRect().GetSize();
		this->hWindow.handle = ::CreateWindowEx(
			WS_EX_ACCEPTFILES,
			windowClass.GetName().CStr(), windowName.CStr(),
			WS_OVERLAPPEDWINDOW,
			x,
			y,
			w,
			h,
			(HWND) hWndParent.handle,
			nullptr,
			(HINSTANCE) windowClass.GetHInstance().handle,
			this
		);
	}
	
	void WWindow::Bind(HWindow pHwnd) noexcept
	{
		Destroy();
		this->hWindow = pHwnd;
	}
	
	void WWindow::Destroy() const
	{
		::DestroyWindow((HWND) this->hWindow.handle);
	}
	
	void WWindow::Show(int32 nCmdShow) const
	{
		::ShowWindow((HWND) this->hWindow.handle, nCmdShow);
	}
	
	void WWindow::Update() const
	{
		::UpdateWindow((HWND) this->hWindow.handle);
	}
	
	
	int64 WWindow::DefaultWindowProc(HWindow hWnd, uint32 msg, uint64 wParam, uint64 lParam)
	{
		return ::DefWindowProc((HWND) hWnd.handle, msg, wParam, lParam);
	}
	
	uint64 WWindow::WindowProc(void *hWnd, uint32 msg, uint64 wParam, int64 lParam)
	{
		WWindow *pThis;
		
		if (msg == WM_NCCREATE)
		{
			auto *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
			pThis = reinterpret_cast<WWindow *>(pCreate->lpCreateParams);
			::SetWindowLongPtr((HWND) hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
			pThis->hWindow.handle = hWnd;
		}
		else
		{
			pThis = reinterpret_cast<WWindow *>(::GetWindowLongPtr((HWND) hWnd, GWLP_USERDATA));
		}
		
		if (pThis) return pThis->OnMessage(msg, wParam, lParam);
		
		return DefaultWindowProc({hWnd}, msg, wParam, lParam);
	}
	
	uint64 WWindow::OnMessage(uint32 msg, uint64 wParam, int64 lParam)
	{
		switch (msg)
		{
			case WM_KEYDOWN:
				return OnKeyDown(EventKeyArgs{wParam});
			case WM_KEYUP:
				return OnKeyUp(EventKeyArgs{wParam});
			case WM_MOUSEMOVE:
			{
				int32 newMouseX = GET_X_LPARAM(lParam);
				int32 newMouseY = GET_Y_LPARAM(lParam);
				int32 deltaX = newMouseX - mousePosition.x;
				int32 deltaY = newMouseY - mousePosition.y;
				mousePosition.x = newMouseX;
				mousePosition.y = newMouseY;
				return OnMouseMoved(
					EventOnMouseMoveArgs{mousePosition.x, mousePosition.y, deltaX, deltaY}
				);
			}
			case WM_ACTIVATE:
				switch (LOWORD(wParam))
				{
					case WA_INACTIVE:
						return OnInactive();
					case WA_ACTIVE:
						return OnActive();
					case WA_CLICKACTIVE:
						return OnClickActive();
					default:
						return 0;
				}
			case WM_MOVE:
			{
				return OnMove(EventOnMoveArgs{.x=LOWORD(lParam), .y=HIWORD(lParam)});
			}
			case WM_CREATE:
			{
				return OnCreate();
			}
			case WM_SIZE:
			{
				return OnResize(EventOnResizeArgs{.width=LOWORD(lParam), .height=HIWORD(lParam)});
			}
			case WM_DROPFILES:
				OnDropFiles(HDrop{(HDROP) wParam});
				::DragFinish((HDROP) wParam);
				return 0;
			case WM_CHAR:
				if (!bEnableOnChar) return DefaultWindowProc(this->hWindow, msg, wParam, lParam);
				return OnChar((TCHAR) wParam);
			case WM_GETMINMAXINFO:
			{
				((MINMAXINFO *) lParam)->ptMinTrackSize.x = this->minSize.width;
				((MINMAXINFO *) lParam)->ptMinTrackSize.y = this->minSize.height;
				((MINMAXINFO *) lParam)->ptMaxTrackSize.x = this->maxSize.width;
				((MINMAXINFO *) lParam)->ptMaxTrackSize.y = this->maxSize.height;
				return 0;
			}
			case WM_IME_STARTCOMPOSITION:
			{
				HIMC hIMC;
				
				hIMC = ImmGetContext((HWND) hWindow.handle);
				
				if (hIMC)
				{
					CANDIDATEFORM candidateForm;
					candidateForm.dwIndex = 0;
					candidateForm.dwStyle = CFS_CANDIDATEPOS;
					candidateForm.ptCurrentPos.x = inputPoint.x;
					candidateForm.ptCurrentPos.y = inputPoint.y;
					ImmSetCandidateWindow(hIMC, &candidateForm);
				}
				else FDebug::LogError(L"ImmGetContext Failed");
				
				ImmReleaseContext((HWND) hWindow.handle, hIMC);
				return 0;
			}
			case WM_IME_COMPOSITION:
			{
				HIMC hIMC;
				DWORD dwSize;
				HGLOBAL hstr;
				LPTSTR lpstr;
				if (!bEnableOnString) return DefaultWindowProc(this->hWindow, msg, wParam, lParam);
				if (lParam & GCS_RESULTSTR)
				{
					hIMC = ImmGetContext((HWND) hWindow.handle);
					
					if (hIMC);
					else FDebug::LogError(L"ImmGetContext Failed");
					
					// Get the size of the result string.
					dwSize = ImmGetCompositionString(hIMC, GCS_RESULTSTR, nullptr, 0);
					
					// increase buffer size for terminating null Char,
					//   maybe it is in UNICODE
					dwSize += sizeof(WCHAR);
					
					hstr = GlobalAlloc(GHND, dwSize);
					if (hstr == nullptr) FDebug::LogError(L"GlobalAlloc Failed");
					
					lpstr = (LPTSTR) GlobalLock(hstr);
					if (lpstr == nullptr) FDebug::LogError(L"GlobalLock Failed");
					
					// Get the result strings that is generated by IME into lpstr.
					ImmGetCompositionString(hIMC, GCS_RESULTSTR, lpstr, dwSize);
					ImmReleaseContext((HWND) hWindow.handle, hIMC);
					
					uint64 result;
					// add this string into text buffer of application
					if (lpstr != nullptr) result = OnString(lpstr);
					
					GlobalUnlock(hstr);
					GlobalFree(hstr);
					return result;
				}
				return 0;
			}
			case WM_SETCURSOR:
				if (LOWORD(lParam) == HTCLIENT)
				{
					// if (hCursor == nullptr) return DefaultWindowProc(this->hWindow, msg, wParam, lParam);
					SetCursor((HCURSOR) hCursor.handle);
					return TRUE;
				}
				return DefaultWindowProc(this->hWindow, msg, wParam, lParam);
			case WM_MENUCHAR:
				// 禁用 alt-enter.
				return MAKELRESULT(0, MNC_CLOSE);
			case WM_CLOSE:
				return OnClose();
			case WM_QUERYENDSESSION:
				return OnQueryEndSession();
			case WM_ENDSESSION:
				return OnEndSession();
			case WM_DESTROY:
				this->hWindow = {};
				return OnDestroy();
			default:
				return DefaultWindowProc(this->hWindow, msg, wParam, lParam);
		}
	}
	
	std::string WWindow::GetNameA() const
	{
		int32 length = ::GetWindowTextLengthA((HWND) this->hWindow.handle);
		auto *buffer = new char[length];
		::GetWindowTextA((HWND) this->hWindow.handle, buffer, length);
		std::string result = buffer;
		delete[] buffer;
		return result;
	}
	
	std::wstring WWindow::GetNameW() const
	{
		int32 length = ::GetWindowTextLengthW((HWND) this->hWindow.handle);
		auto *buffer = new wchar_t[length];
		::GetWindowTextW((HWND) this->hWindow.handle, buffer, length);
		std::wstring result = buffer;
		delete[] buffer;
		return result;
	}
	
	void WWindow::SetName(const std::string &name)
	{
		::SetWindowTextA((HWND) this->hWindow.handle, name.c_str());
	}
	
	void WWindow::SetName(const std::wstring &name)
	{
		::SetWindowTextW((HWND) this->hWindow.handle, name.c_str());
	}
	
	HWindow WWindow::DesktopWindow()
	{
		return {::GetDesktopWindow()};
	}
	
	FRectI WWindow::GetRect() const
	{
		RECT rect;
		::GetWindowRect((HWND) hWindow.handle, &rect);
		return Whale::FRectI(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
	}
	
	void WWindow::SetRect(const FRectI &rect)
	{
		::MoveWindow((HWND) hWindow.handle, rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, true);
	}
	
	
} // Whale