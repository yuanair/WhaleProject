//
// Created by admin on 2024/7/5.
//

#include "WProgram.hpp"
#include "FPlatformManager.hpp"
#include <Whale/FDebug.hpp>
#include <Whale/FCore.hpp>

#include <Windows.h>
#include <format>

namespace Whale
{
	void WProgram::OnBeginPlay()
	{
	
	}
	
	void WProgram::OnTick(Double deltaTime)
	{
	
	}
	
	void WProgram::OnEndPlay()
	{
	
	}
	
	
	void WProgram::BeginPlay()
	{
		FDebug::Log<Char>(Info, logTag, WTEXT("Start"));
		FDebug::Log<Char>(
			Info, logTag, std::format(
				WTEXT("{0} | {1} {2}{0} | IsRunAsAdministrator: {3}{0} | System: {4} {5}"),
				FPlatformManager::Get().GetPlatform().GetNewLine().CStr(),
				FCore::GetAppName(), FCore::GetVersion(),
				FPlatformManager::Get().GetPlatform().IsRunAsAdministrator() ? WTEXT("true") : WTEXT("false"),
				FPlatformManager::Get().GetPlatform().GetName().CStr(),
				FPlatformManager::Get().GetPlatform().GetVersion().CStr()
			).c_str());
		GetTimer()->Reset();
		OnBeginPlay();
	}
	
	void WProgram::Tick()
	{
		GetTimer()->Tick();
		OnTick(GetTimer()->GetDeltaTime());
	}
	
	void WProgram::EndPlay()
	{
		OnEndPlay();
		FDebug::Log<Char>(Info, logTag, WTEXT("End"));
		FDebug::LogFlush();
		FDebug::LogClose();
	}
	
	WProgram::WProgram(WGenericTimer *pTimer) : pTimer(pTimer) {}
	
	WProgram::~WProgram()
	{
		if (this->pTimer) delete this->pTimer;
		this->pTimer = nullptr;
	}
	
	
} // Whale