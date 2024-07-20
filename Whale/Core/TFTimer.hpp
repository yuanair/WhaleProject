//
// Created by admin on 2024/2/3.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"

#include <chrono>
#include <cmath>

namespace Whale
{
	///
	/// 计时器
	template<class ClockT = std::chrono::system_clock>
	class WHALE_API TFTimer
	{
	public:
		
		typedef ClockT Clock;
		
		typedef typename Clock::time_point TimePoint;
		
		typedef typename Clock::duration Duration;
		
		typedef typename Clock::rep Rep;
	
	public:
		
		inline TFTimer()
			: tickCount(0), fps(0.0)
		{
			Restart();
		}
		
		inline ~TFTimer() = default;
	
	public:
		
		///
		/// \return 现在时间
		inline static TimePoint NowTime() noexcept
		{
			return Clock::now();
		}
	
	public:
		
		///
		/// 重新开始记时
		inline void Restart()
		{
			this->startTimePoint = NowTime();
			this->lastTickTimePoint = this->startTimePoint;
			
			this->fpsCalculateDeltaTime = Duration::zero();
			// this->fpsCalculateDeltaTimeMin;
			
			this->deltaTime = Duration();
			
			this->tickCount = 0;
			
			this->fps = NAN;
		}
		
		///
		/// 一般每帧调用
		inline void Tick()
		{
			TimePoint now = NowTime();
			
			this->deltaTime = now - this->lastTickTimePoint;
			this->fpsCalculateDeltaTime += this->deltaTime;
			
			if (this->fpsCalculateDeltaTime >= this->fpsCalculateDeltaTimeMin)
			{
				this->fps =
					(double_t) (this->tickCount) / std::chrono::duration<double_t>(this->fpsCalculateDeltaTime).count();
				this->tickCount = 0;
				this->fpsCalculateDeltaTime = Duration::zero();
			}
			
			this->lastTickTimePoint = now;
			this->tickCount++;
		}
	
	public:
		
		///
		/// \return 最后Tick时间到现在的时间间隔
		inline Duration LastTickToNow() const
		{
			return NowTime() - lastTickTimePoint;
		}
		
		///
		/// \return 开始时间到现在的时间间隔
		inline Duration StartToNow() const
		{
			return NowTime() - startTimePoint;
		}
		
		///
		/// \return 开始时间到最后Tick的时间间隔
		inline Duration StartToLastTick() const
		{
			return lastTickTimePoint - startTimePoint;
		}
	
	public:
		
		///
		/// \return 开始时间
		inline TimePoint GetStartTimePoint() const noexcept { return this->startTimePoint; }
		
		///
		/// \return 最后Tick时间
		inline TimePoint GetLastTickTimePoint() const noexcept { return this->lastTickTimePoint; }
		
		///
		/// \return Tick间隔时间
		inline Duration GetDeltaTime() const noexcept { return this->deltaTime; }
		
		///
		/// \return Tick间隔时间（单位：秒）
		[[nodiscard]]
		inline float_t GetDeltaTimeF() const noexcept { return std::chrono::duration<float_t>(GetDeltaTime()).count(); }
		
		///
		/// \return Tick间隔时间（单位：秒）
		[[nodiscard]]
		inline double_t GetDeltaTimeD() const noexcept
		{
			return std::chrono::duration<double_t>(
				GetDeltaTime()).count();
		}
		
		///
		/// \return FPS
		[[nodiscard]]
		inline double_t GetFps() const noexcept { return this->fps; }
		
		///
		/// \return FPS
		[[nodiscard]]
		inline int32_t GetFpsI() const noexcept { return (int32_t) this->fps; }
		
		///
		/// \return FPS
		[[nodiscard]]
		inline float_t GetFpsF() const noexcept { return (float_t) this->fps; }
		
		///
		/// \return FPS计算间隔时间
		inline Duration GetFpsCalculateDeltaTimeMin() const noexcept { return fpsCalculateDeltaTimeMin; }
		
		///
		/// \param newFpsCalculateDeltaTimeMin FPS计算间隔时间
		inline void SetFpsCalculateDeltaTimeMin(
			Duration newFpsCalculateDeltaTimeMin) { this->fpsCalculateDeltaTimeMin = newFpsCalculateDeltaTimeMin; }
	
	private:
		
		TimePoint startTimePoint;
		TimePoint lastTickTimePoint;
		
		Duration deltaTime;
		Duration fpsCalculateDeltaTime;
		Duration fpsCalculateDeltaTimeMin = std::chrono::seconds(1);
		
		uint32_t tickCount;
		
		double_t fps;
		
		
	};
	
} // GenesisCube
