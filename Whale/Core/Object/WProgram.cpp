//
// Created by admin on 2024/7/5.
//

#include <Windows.h>
#include "WProgram.hpp"
#include "Whale/Core/Debug/FDebug.hpp"

namespace Whale
{
	void WProgram::OnBeginPlay()
	{
	
	}
	
	void WProgram::OnTick(Float deltaTime)
	{
	
	}
	
	void WProgram::OnEndPlay()
	{
	
	}
	
	int32 WProgram::Run()
	{
		MSG msg;
		
		FDebug::LogInfo(WProgram::GetAppNameW(), L"WProgram Start");
		FDebug::LogInfo(WProgram::GetAppNameW(), (std::wstring() + GetAppNameW() + L" " + GetVersionW()).c_str());
		
		GetTimer().Restart();
		OnBeginPlay();
		do
		{
			if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			else
			{
				GetTimer().Tick();
				OnTick(GetTimer().GetDeltaTimeF());
			}
		}
		while (msg.message != WM_QUIT);
		
		OnEndPlay();
		FDebug::LogInfo(WProgram::GetAppNameW(), L"WProgram End");
		FDebug::LogFlush();
		
		return (int) msg.wParam;
	}
	
	const Char *WProgram::GetAppNameA()
	{
		return "Whale";
	}
	
	const WChar *WProgram::GetAppNameW()
	{
		return L"Whale";
	};
	
	const Char *WProgram::GetVersionA()
	{
		return "0.1.0-alpha";
	}
	
	const WChar *WProgram::GetVersionW()
	{
		return L"0.1.0-alpha";
	}
	
	const Char *WProgram::GetBuildDataA()
	{
		return __DATE__;
	}
	
	const WChar *WProgram::GetBuildDataW()
	{
		return L"" __DATE__;
	}
	
} // Whale