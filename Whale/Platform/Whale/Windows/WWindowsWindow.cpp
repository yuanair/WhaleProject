//
// Created by admin on 2024/7/1.
//

#include "WWindowsWindow.hpp"

#include "FCore.hpp"
#include "Whale/FDebug.hpp"

#include <windows.h>
#include <windowsx.h>

namespace Whale
{
	
	
	WWindowsWindow::WWindowsWindow()
		: inputPoint{}, hCursor{::LoadCursorW(nullptr, IDC_ARROW)},
		  minSize{0, 0}, maxSize{DesktopWindowSize()}, mousePosition{}
	{
	
	}
	
	WWindowsWindow::~WWindowsWindow()
	{
		Destroy();
	}
	
	void WWindowsWindow::Create(const FWindowCreateArg &arg)
	{
		this->hWindow.handle = ::CreateWindowExW(
			WS_EX_ACCEPTFILES,
			arg.m_class->GetName().CStr(), arg.m_name.CStr(),
			WS_OVERLAPPEDWINDOW,
			arg.m_x,
			arg.m_y,
			arg.m_width,
			arg.m_height,
			nullptr,
			nullptr,
			::GetModuleHandleW(nullptr),
			this
		);
		FCore::GetLastError().LogIfFailed(logTag);
	}
	
	void WWindowsWindow::Bind(HWindow pHwnd) noexcept
	{
		Destroy();
		this->hWindow = pHwnd;
	}
	
	void WWindowsWindow::Destroy()
	{
		if (this->hWindow.handle == nullptr) return;
		::DestroyWindow((HWND) this->hWindow.handle);
		// this->hWindow.handle = nullptr; // 在ON_DESTROY事件中重置
	}
	
	void WWindowsWindow::Show(int32 nCmdShow) const
	{
		::ShowWindow((HWND) this->hWindow.handle, nCmdShow);
	}
	
	void WWindowsWindow::Update() const
	{
		::UpdateWindow((HWND) this->hWindow.handle);
	}
	
	
	void WWindowsWindow::MessageHanding()
	{
		MSG msg;
		m_inputSystem.Tick();
		if (::PeekMessageW(&msg, (HWND) this->hWindow.handle, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessageW(&msg);
		}
	}
	
	LResult WWindowsWindow::DefaultWindowProc(HWindow hWnd, UInt msg, WParam wParam, LParam lParam)
	{
		return ::DefWindowProcW((HWND) hWnd.handle, msg, wParam, lParam);
	}
	
	LResult WWindowsWindow::WindowProc(void *hWnd, UInt msg, WParam wParam, LParam lParam) noexcept
	{
		WWindowsWindow *pThis;
		
		if (msg == WM_NCCREATE)
		{
			auto *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
			pThis = reinterpret_cast<WWindowsWindow *>(pCreate->lpCreateParams);
			::SetWindowLongPtrW((HWND) hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
			pThis->hWindow.handle = hWnd;
		}
		else
		{
			pThis = reinterpret_cast<WWindowsWindow *>(::GetWindowLongPtrW((HWND) hWnd, GWLP_USERDATA));
		}
		
		try
		{
			if (pThis) return pThis->OnMessage(msg, wParam, lParam);
		}
		catch (FException &e)
		{
			FDebug::Log<Char>(Error, logTag, FString(WTEXT("Exception::")) + e.What());
		}
		
		return DefaultWindowProc({hWnd}, msg, wParam, lParam);
	}
	
	LResult WWindowsWindow::OnMessage(UInt msg, WParam wParam, LParam lParam)
	{
		switch (msg)
		{
			case WM_KEYDOWN:
				m_inputSystem.PressKey(EKeyType(wParam));
				return 0;
			case WM_KEYUP:
				m_inputSystem.ReleaseKey(EKeyType(wParam));
				return 0;
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
				m_inputSystem.onCreate.Call(this);
				return OnCreate();
			}
			case WM_SIZE:
			{
				m_inputSystem.onResize.Press({.x=LOWORD(lParam), .y=HIWORD(lParam)});
				return OnResize(EventOnResizeArgs{.width=LOWORD(lParam), .height=HIWORD(lParam)});
			}
			case WM_DROPFILES:
				m_inputSystem.onDrop.Call(HDrop{(HDROP) wParam});
				return OnDropFiles(HDrop{(HDROP) wParam});
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
				else FDebug::Log<Char>(Error, logTag, WTEXT("ImmGetContext Failed"));
				
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
					else FDebug::Log<Char>(Error, logTag, WTEXT("ImmGetContext Failed"));
					
					// Read the size of the result string.
					dwSize = ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, nullptr, 0);
					
					// increase buffer size for terminating null CharA,
					//   maybe it is in UNICODE
					dwSize += sizeof(WCHAR);
					
					hstr = GlobalAlloc(GHND, dwSize);
					if (hstr == nullptr) FDebug::Log<Char>(Error, logTag, WTEXT("GlobalAlloc Failed"));
					
					lpstr = (LPTSTR) GlobalLock(hstr);
					if (lpstr == nullptr) FDebug::Log<Char>(Error, logTag, WTEXT("GlobalLock Failed"));
					
					// Read the result strings that is generated by IME into lpstr.
					ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, lpstr, dwSize);
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
					SetCursor((HCURSOR) hCursor.handle);
					return TRUE;
				}
				return DefaultWindowProc(this->hWindow, msg, wParam, lParam);
			case WM_MENUCHAR:
				// 禁用 alt-enter.
				return MAKELRESULT(0, MNC_CLOSE);
			case WM_CLOSE:
				m_inputSystem.PressCloseButton();
				m_inputSystem.ReleaseCloseButton();
				return 0;
			case WM_QUERYENDSESSION:
				return OnQueryEndSession();
			case WM_ENDSESSION:
				return OnEndSession();
			case WM_DESTROY:
			{
				m_inputSystem.onDestroy.Call(this);
				auto result = OnDestroy();
				this->hWindow.handle = nullptr;
				return result;
			}
			default:
				return DefaultWindowProc(this->hWindow, msg, wParam, lParam);
		}
	}
	
	StringA WWindowsWindow::GetNameA() const
	{
		int32   length = ::GetWindowTextLengthA((HWND) this->hWindow.handle) + 1;
		StringA buffer{nullptr, (SizeT) length};
		::GetWindowTextA((HWND) this->hWindow.handle, buffer.GetPtr(), length);
		return buffer;
	}
	
	StringW WWindowsWindow::GetNameW() const
	{
		int32   length = ::GetWindowTextLengthW((HWND) this->hWindow.handle) + 1;
		StringW buffer{nullptr, (SizeT) length};
		::GetWindowTextW((HWND) this->hWindow.handle, buffer.GetPtr(), length);
		return buffer;
	}
	
	void WWindowsWindow::SetName(const StringA &name)
	{
		::SetWindowTextA((HWND) this->hWindow.handle, name.CStr());
	}
	
	void WWindowsWindow::SetName(const StringW &name)
	{
		::SetWindowTextW((HWND) this->hWindow.handle, name.CStr());
	}
	
	HWindow WWindowsWindow::DesktopWindow()
	{
		return {::GetDesktopWindow()};
	}
	
	Eigen::Vector2i WWindowsWindow::DesktopWindowSize()
	{
		RECT rect;
		::GetWindowRect(::GetDesktopWindow(), &rect);
		return {rect.right - rect.left, rect.bottom - rect.top};
	}
	
	Eigen::Vector4i WWindowsWindow::GetRect() const
	{
		RECT rect;
		::GetWindowRect((HWND) hWindow.handle, &rect);
		return {rect.left, rect.top, rect.right, rect.bottom};
	}
	
	void WWindowsWindow::SetRect(const Eigen::Vector4i &rect)
	{
		::MoveWindow((HWND) hWindow.handle, rect.x(), rect.y(), rect.z(), rect.w(), true);
	}
	
	Bool WWindowsWindow::GetFileDragAndDropPermission() const noexcept
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