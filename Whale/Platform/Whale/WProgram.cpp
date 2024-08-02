//
// Created by admin on 2024/7/5.
//

#include "WProgram.hpp"
#include <Whale/FDebug.hpp>
#include <Whale/FCore.hpp>

#include <Windows.h>

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
		
		BeginPlay();
		
		do
		{
			if (::PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessageA(&msg);
			}
			else
			{
				Tick();
			}
		}
		while (msg.message != WM_QUIT);
		
		EndPlay();
		
		return (int32) msg.wParam;
	}
	
	
	void WProgram::BeginPlay()
	{
		FDebug::Log<Char>(Info, WhaleTag, WTEXT("WProgram Start"));
		FDebug::Log<Char>(
			Info, WhaleTag, std::format(WTEXT("{} {}"), FCore::GetAppName(), FCore::GetVersion()).c_str());
		GetTimer().Restart();
		OnBeginPlay();
	}
	
	void WProgram::Tick()
	{
		GetTimer().Tick();
		OnTick(GetTimer().GetDeltaTimeF());
	}
	
	void WProgram::EndPlay()
	{
		OnEndPlay();
		FDebug::Log<Char>(Info, WhaleTag, WTEXT("WProgram End"));
		FDebug::LogFlush();
		FDebug::LogClose();
	}
	
	
} // Whale