//
// Created by admin on 2024/7/1.
//

#include "WWindow.hpp"

#include "FCore.hpp"

#include <windows.h>
#include <windowsx.h>

#pragma comment(lib, "Imm32.lib")

namespace Whale::Win32
{
	
	bool WWindow::WWindowClass::Register(HIcon hIcon, HIcon hIconSm)
	{
		if (hIcon.handle == nullptr) hIcon.handle     = ::LoadIcon(nullptr, IDI_APPLICATION);
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
		return (bool) ::RegisterClassEx(&wnd);
	}
	
	Bool WWindow::WWindowClass::Unregister()
	{
		return ::UnregisterClass(this->name.CStr(), (HINSTANCE) this->hInstance.handle);
	}
	
	WWindow::WWindow()
		: inputPoint{}, hCursor{::LoadCursor(nullptr, IDC_ARROW)},
		  minSize{}, maxSize{DesktopWindowSize()}, mousePosition{}
	{
	
	}
	
	WWindow::~WWindow()
	{
		Destroy();
	}

//	void WWindow::Init(
//		const WWindowClass &windowClass, const StringA &windowName,
//		int32 x, int32 y, int32 w, int32 h, HWindow hWndParent
//	)
//	{
//		WWindow desktop;
//		desktop.Bind(DesktopWindow());
//		this->maxSize = desktop.GetRect().GetSize();
//		this->hWindow.handle = ::CreateWindowExA(
//			WS_EX_ACCEPTFILES,
//			windowClass.GetName().CStr(), windowName.CStr(),
//			WS_OVERLAPPEDWINDOW,
//			x,
//			y,
//			w,
//			h,
//			(HWND) hWndParent.handle,
//			nullptr,
//			(HINSTANCE) windowClass.GetHInstance().handle,
//			this
//		);
//	}
	
	void WWindow::Create(
		const WWindowClass &windowClass, const StringT &windowName,
		int32 x, int32 y, int32 w, int32 h, HWindow hWndParent
	)
	{
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
	
	void WWindow::Destroy()
	{
		::DestroyWindow((HWND) this->hWindow.handle);
		// this->hWindow.handle = nullptr; // 在ON_DESTROY事件中重置
	}
	
	void WWindow::Show(int32 nCmdShow) const
	{
		::ShowWindow((HWND) this->hWindow.handle, nCmdShow);
	}
	
	void WWindow::Update() const
	{
		::UpdateWindow((HWND) this->hWindow.handle);
	}
	
	
	LResult WWindow::DefaultWindowProc(HWindow hWnd, UInt msg, WParam wParam, LParam lParam)
	{
		return ::DefWindowProc((HWND) hWnd.handle, msg, wParam, lParam);
	}
	
	LResult WWindow::WindowProc(void *hWnd, UInt msg, WParam wParam, LParam lParam)
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
	
	LResult WWindow::OnMessage(UInt msg, WParam wParam, LParam lParam)
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
				int32 deltaX    = newMouseX - mousePosition.x();
				int32 deltaY    = newMouseY - mousePosition.y();
				mousePosition.x() = newMouseX;
				mousePosition.y() = newMouseY;
				return OnMouseMoved(
					EventOnMouseMoveArgs{mousePosition.x(), mousePosition.y(), deltaX, deltaY}
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
				((MINMAXINFO *) lParam)->ptMinTrackSize.x = this->minSize.x();
				((MINMAXINFO *) lParam)->ptMinTrackSize.y = this->minSize.y();
				((MINMAXINFO *) lParam)->ptMaxTrackSize.x = this->maxSize.x();
				((MINMAXINFO *) lParam)->ptMaxTrackSize.y = this->maxSize.y();
				return 0;
			}
			case WM_IME_STARTCOMPOSITION:
			{
				HIMC hIMC;
				
				hIMC = ImmGetContext((HWND) hWindow.handle);
				
				if (hIMC)
				{
					CANDIDATEFORM candidateForm;
					candidateForm.dwIndex        = 0;
					candidateForm.dwStyle        = CFS_CANDIDATEPOS;
					candidateForm.ptCurrentPos.x = inputPoint.x();
					candidateForm.ptCurrentPos.y = inputPoint.y();
					ImmSetCandidateWindow(hIMC, &candidateForm);
				}
				else FDebug::LogError(TagW, L"ImmGetContext Failed");
				
				ImmReleaseContext((HWND) hWindow.handle, hIMC);
				return 0;
			}
			case WM_IME_COMPOSITION:
			{
				HIMC    hIMC;
				DWORD   dwSize;
				HGLOBAL hstr;
				LPTSTR  lpstr;
				if (!bEnableOnString) return DefaultWindowProc(this->hWindow, msg, wParam, lParam);
				if (lParam & GCS_RESULTSTR)
				{
					hIMC = ImmGetContext((HWND) hWindow.handle);
					
					if (hIMC);
					else FDebug::LogError(TagW, L"ImmGetContext Failed");
					
					// Read the size of the result string.
					dwSize = ImmGetCompositionString(hIMC, GCS_RESULTSTR, nullptr, 0);
					
					// increase buffer size for terminating null CharA,
					//   maybe it is in UNICODE
					dwSize += sizeof(WCHAR);
					
					hstr = GlobalAlloc(GHND, dwSize);
					if (hstr == nullptr) FDebug::LogError(TagW, L"GlobalAlloc Failed");
					
					lpstr = (LPTSTR) GlobalLock(hstr);
					if (lpstr == nullptr) FDebug::LogError(TagW, L"GlobalLock Failed");
					
					// Read the result strings that is generated by IME into lpstr.
					ImmGetCompositionString(hIMC, GCS_RESULTSTR, lpstr, dwSize);
					ImmReleaseContext((HWND) hWindow.handle, hIMC);
					
					LResult result = 0;
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
			{
				auto result = OnDestroy();
				this->hWindow.handle = nullptr;
				return result;
			}
			default:
				return DefaultWindowProc(this->hWindow, msg, wParam, lParam);
		}
	}
	
	StringA WWindow::GetNameA() const
	{
		int32   length = ::GetWindowTextLengthA((HWND) this->hWindow.handle) + 1;
		StringA buffer{nullptr, (SizeT) length};
		::GetWindowTextA((HWND) this->hWindow.handle, buffer.GetPtr(), length);
		return buffer;
	}
	
	StringW WWindow::GetNameW() const
	{
		int32   length = ::GetWindowTextLengthW((HWND) this->hWindow.handle) + 1;
		StringW buffer{nullptr, (SizeT) length};
		::GetWindowTextW((HWND) this->hWindow.handle, buffer.GetPtr(), length);
		return buffer;
	}
	
	void WWindow::SetName(const StringA &name)
	{
		::SetWindowTextA((HWND) this->hWindow.handle, name.CStr());
	}
	
	void WWindow::SetName(const StringW &name)
	{
		::SetWindowTextW((HWND) this->hWindow.handle, name.CStr());
	}
	
	HWindow WWindow::DesktopWindow()
	{
		return {::GetDesktopWindow()};
	}
	
	Eigen::Vector2i WWindow::DesktopWindowSize()
	{
		RECT rect;
		::GetWindowRect(::GetDesktopWindow(), &rect);
		return {rect.right - rect.left, rect.bottom - rect.top};
	}
	
	Eigen::Vector4i WWindow::GetRect() const
	{
		RECT rect;
		::GetWindowRect((HWND) hWindow.handle, &rect);
		return {rect.left, rect.top, rect.right, rect.bottom};
	}
	
	void WWindow::SetRect(const Eigen::Vector4i &rect)
	{
		::MoveWindow((HWND) hWindow.handle, rect.x(), rect.y(), rect.z(), rect.w(), true);
	}
	
	Bool WWindow::GetFileDragAndDropPermission() const noexcept
	{
		if (!ChangeWindowMessageFilterEx(
			(HWND) this->hWindow.handle, WM_DROPFILES, MSGFLT_ADD, nullptr
		))
			return false;
		if (!ChangeWindowMessageFilterEx(
			(HWND) this->hWindow.handle, WM_COPYDATA, MSGFLT_ADD, nullptr
		))
			return false;
		if (!ChangeWindowMessageFilterEx(
			(HWND) this->hWindow.handle, 0x49 /* WM_COPYGLOBALDATA */, MSGFLT_ADD, nullptr
		))
			return false;
		return true;
	}
	
	
} // Whale