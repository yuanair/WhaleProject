//
// Created by admin on 2024/8/3.
//

#pragma once


#include <Whale/TypeDef.hpp>
#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>

namespace Whale
{
	
	/// 计时器
	class WHALE_API WGenericTimer : public WObject
	{
	public:
		
		WGenericTimer() = default;
		
		WGenericTimer(const WGenericTimer &) = delete;
	
	public:
		
		WGenericTimer &operator=(const WGenericTimer &) = delete;
	
	public:
		
		/// 时间膨胀最小值
		static constexpr Double TimeDilationMinimum = 1e-5;
		
		/// 时间膨胀最大值
		static constexpr Double TimeDilationMaximum = 1e+3;
	
	public:
		
		/// 重置
		virtual void Reset() = 0;
		
		/// 解除暂停
		virtual void Start() = 0;
		
		/// 暂停
		virtual void Stop() = 0;
		
		/// 每帧调用
		virtual void Tick() = 0;
		
		/// 设置时间膨胀倍数（仅对DeltaTime()有影响）小于1.0为减速，大于1.0为加速。
		virtual void SetTimeDilation(Double value) = 0;
		
		/// 获取从开始到上一次调用Tick的时间 (单位：秒）
		[[nodiscard]] virtual Double TotalTime() const = 0;
		
		/// 获取硬件支持的最小计数器时间间隔（单位：秒）
		[[nodiscard]] virtual Double GetSecondsPerCount() const = 0;
		
		/// 获取硬件支持的最大计数器频率（以每秒计数为单位）
		[[nodiscard]] virtual int64 QueryPerformanceFrequency() const = 0;
		
		/// 获取时间膨胀倍数
		[[nodiscard]] virtual Double GetTimeDilation() const = 0;
		
		/// 获取帧间隔时间 (单位：秒）
		[[nodiscard]] virtual Double GetDeltaTime() const = 0;
		
		/// 获取帧间隔时间 (单位：秒）
		[[nodiscard]] virtual Float GetDeltaTimeF() const = 0;
		
		/// 获取帧率
		[[nodiscard]] virtual Double GetFps() const = 0;
		
		/// 是否已经暂停
		[[nodiscard]] virtual Bool IsStop() const = 0;
		
	};
	
} // Whale
