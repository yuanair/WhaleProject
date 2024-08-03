//
// Created by admin on 2024/8/3.
//

#pragma once

#include "HWinDef.hpp"

#include "../WGenericTimer.hpp"

namespace Whale
{
	
	class WHALE_API WWindowsTimer : public WGenericTimer
	{
	public:
		
		WWindowsTimer();
	
	public:
		
		void Reset() override;
		
		void Start() override;
		
		void Stop() override;
		
		void Tick() override;
		
		void SetTimeDilation(Double value) override;
		
		[[nodiscard]]
		Double TotalTime() const override;
		
		[[nodiscard]]
		Double GetSecondsPerCount() const override;
		
		[[nodiscard]]
		int64 QueryPerformanceFrequency() const override;
		
		[[nodiscard]]
		inline Double GetTimeDilation() const override { return this->timeDilation; }
		
		[[nodiscard]]
		inline Double GetDeltaTime() const override { return this->deltaTime; }
		
		[[nodiscard]]
		inline Float GetDeltaTimeF() const override { return static_cast<Float>(this->deltaTime); }
		
		[[nodiscard]]
		inline Double GetFps() const override { return this->fps; }
		
		[[nodiscard]]
		inline Bool IsStop() const override { return bIsStopped; }
	
	private:
		
		Double deltaTime;
		Double fps;
		Double timeDilation;
		
		int64 baseTime;
		int64 pausedTime;
		int64 stopTime;
		int64 prevTime;
		int64 currTime;
		
		int64 lastCalculatorFpsTime;
		int64 tickCount;
		
		Bool bIsStopped;
		
	};
	
} // Whale
