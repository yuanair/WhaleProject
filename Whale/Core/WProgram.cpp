//
// Created by admin on 2024/7/5.
//

#include <Windows.h>
#include "WProgram.hpp"
#include "TTimer.hpp"
#include "FDebug.hpp"

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
		
		FDebug::LogInfo(L"WProgram Start");
		FDebug::LogInfo((std::wstring() + AppNameW + VersionW).c_str());
		
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
		FDebug::LogInfo(L"WProgram End");
		FDebug::LogFlush();
		
		return (int) msg.wParam;
	}
	
	const Char WProgram::AppNameA[] = "Whale";
	
	const WChar WProgram::AppNameW[] = L"Whale";
	
	const Char WProgram::VersionA[] = "0.1.0-alpha";
	
	const WChar WProgram::VersionW[] = L"0.1.0-alpha";
	
	const Char WProgram::BuildDataA[] = __DATE__;
	
	const WChar WProgram::BuildDataW[] = L"" __DATE__;
	
} // Whale