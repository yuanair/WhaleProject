//
// Created by admin on 2024/7/5.
//

#include "WProgram.hpp"
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
		FDebug::Log<Char>(Info, WhaleTag, WTEXT("WProgram Start"));
		FDebug::Log<Char>(
			Info, WhaleTag, std::format(WTEXT("{} {}"), FCore::GetAppName(), FCore::GetVersion()).c_str());
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
		FDebug::Log<Char>(Info, WhaleTag, WTEXT("WProgram End"));
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