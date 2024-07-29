//
// Created by admin on 2024/7/5.
//

#include <Windows.h>
#include "WProgram.hpp"
#include "Whale/Core/FDebug.hpp"
#include "Whale/Core/FCore.hpp"

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
	
	int32 WProgram::Run(const StringA &)
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
	
	int32 WProgram::Run(const StringW &)
	{
		MSG msg;
		
		BeginPlay();
		
		do
		{
			if (::PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessageW(&msg);
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
		FDebug::LogInfo(WhaleTagA, "WProgram Start");
		FDebug::LogInfo(WhaleTagA, std::format("{} {}", FCore::GetAppNameA(), FCore::GetVersionA()).c_str());
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
		FDebug::LogInfo(WhaleTagA, "WProgram End");
		FDebug::LogFlush();
		FDebug::LogClose();
	}
	
	
} // Whale