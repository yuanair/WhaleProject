//
// Created by admin on 2024/7/5.
//

#include <Windows.h>
#include "WProgram.hpp"
#include "Whale/Core/FDebug.hpp"

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
	
	int32 WProgram::RunA()
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
	
	int32 WProgram::RunW()
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
		try
		{
			FDebug::LogInfo(WProgram::GetAppNameA(), "WProgram Start");
			FDebug::LogInfo(WProgram::GetAppNameA(), std::format("{} {}", GetAppNameA(), GetVersionA()).c_str());
			GetTimer().Restart();
			OnBeginPlay();
		}
		catch (const std::exception &exception)
		{
			FDebug::LogFatal(
				WProgram::GetAppNameA(), std::format(
					"OnEndPlay(): {}: {}", typeid(exception).name(),
					exception.what()).c_str());
			throw exception;
		}
	}
	
	void WProgram::Tick()
	{
		try
		{
			GetTimer().Tick();
			OnTick(GetTimer().GetDeltaTimeF());
		}
		catch (const std::exception &exception)
		{
			FDebug::LogFatal(
				WProgram::GetAppNameA(), std::format(
					"OnEndPlay(): {}: {}", typeid(exception).name(),
					exception.what()).c_str());
			throw exception;
		}
	}
	
	void WProgram::EndPlay()
	{
		try
		{
			OnEndPlay();
		}
		catch (const std::exception &exception)
		{
			FDebug::LogFatal(
				WProgram::GetAppNameA(), std::format(
					"OnEndPlay(): {}: {}", typeid(exception).name(),
					exception.what()).c_str());
			throw exception;
		}
		FDebug::LogInfo(WProgram::GetAppNameA(), "WProgram End");
		FDebug::LogFlush();
		FDebug::LogClose();
	}
	
	const CharA *WProgram::GetAppNameA()
	{
		return "Whale";
	}
	
	const CharW *WProgram::GetAppNameW()
	{
		return L"Whale";
	};
	
	const CharA *WProgram::GetVersionA()
	{
		return "0.1.0-alpha";
	}
	
	const CharW *WProgram::GetVersionW()
	{
		return L"0.1.0-alpha";
	}
	
	const CharA *WProgram::GetBuildDataA()
	{
		return __DATE__;
	}
	
	const CharW *WProgram::GetBuildDataW()
	{
		return L"" __DATE__;
	}
	
} // Whale