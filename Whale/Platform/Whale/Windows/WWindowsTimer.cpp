//
// Created by admin on 2024/8/3.
//

#include "WWindowsTimer.hpp"

#include <Windows.h>

namespace Whale
{
	
	WWindowsTimer::WWindowsTimer()
		: deltaTime{},
		  fps{},
		  timeDilation{},
		  baseTime{},
		  pausedTime{},
		  stopTime{},
		  prevTime{},
		  currTime{},
		  lastCalculatorFpsTime{},
		  tickCount{},
		  bIsStopped{}
	{
		Reset();
	}
	
	int64 WWindowsTimer::QueryPerformanceFrequency() const
	{
		int64 countsPerSec = 0;
		::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER *>(&countsPerSec));
		return countsPerSec;
	}
	
	Double WWindowsTimer::GetSecondsPerCount() const
	{
		static Double secondsPerCount = 1.0 / (Double) QueryPerformanceFrequency();
		return secondsPerCount;
	}
	
	void WWindowsTimer::Reset()
	{
		int64_t curr = 0;
		::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER *>(&curr));
		
		deltaTime    = 0.0;
		fps          = 0.0;
		timeDilation = 1.0;
		
		baseTime   = curr;
		pausedTime = 0;
		stopTime   = 0;
		prevTime   = curr;
		currTime   = curr;
		
		lastCalculatorFpsTime = curr;
		tickCount             = 0;
		
		bIsStopped = false;
	}
	
	void WWindowsTimer::Start()
	{
		int64_t startTime = 0;
		::QueryPerformanceCounter((LARGE_INTEGER *) &startTime);
		
		if (bIsStopped)
		{
			pausedTime += (startTime - stopTime);
			
			prevTime = startTime;
			
			stopTime   = 0;
			bIsStopped = false;
		}
	}
	
	void WWindowsTimer::Stop()
	{
		if (bIsStopped) return;
		int64_t curr = 0;
		::QueryPerformanceCounter((LARGE_INTEGER *) &curr);
		
		stopTime   = curr;
		bIsStopped = true;
	}
	
	void WWindowsTimer::Tick()
	{
		if (bIsStopped)
		{
			deltaTime = 0.0;
			return;
		}
		
		int64_t curr = 0;
		::QueryPerformanceCounter((LARGE_INTEGER *) &curr);
		currTime = curr;
		
		deltaTime = Double(currTime - prevTime) * GetSecondsPerCount() * timeDilation;
		
		prevTime = currTime;
		
		// deltaTime有可能为负值，非暂停时期DeltaTime不应为0
		if (deltaTime < 1E-5)
		{
			deltaTime = 1E-5;
		}
		
		tickCount++;
		Double calculatorFpsDeltaTime = Double(currTime - lastCalculatorFpsTime) * GetSecondsPerCount();
		if (calculatorFpsDeltaTime > 1.0)
		{
			fps = Double(tickCount) / calculatorFpsDeltaTime;
			
			tickCount             = 0;
			lastCalculatorFpsTime = currTime;
		}
	}
	
	void WWindowsTimer::SetTimeDilation(Double value)
	{
		this->timeDilation = value < TimeDilationMinimum ? TimeDilationMinimum : (
			value > TimeDilationMaximum ? TimeDilationMaximum : value
		);
	}
	
	Double WWindowsTimer::TotalTime() const
	{
		if (bIsStopped)
		{
			return Double(stopTime - pausedTime - baseTime) * GetSecondsPerCount();
		}
		else
		{
			return Double(currTime - pausedTime - baseTime) * GetSecondsPerCount();
		}
	}
	
} // Whale