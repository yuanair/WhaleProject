//
// Created by admin on 2024/8/4.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>

namespace Whale
{
	
	/// 时间
	struct FTime
	{
		/// 年
		uint32 year;
		/// 月
		uint8  month;
		/// 星期
		uint8  dayOfWeek;
		/// 日
		uint8  day;
		/// 小时
		uint8  hour;
		/// 分钟
		uint8  minute;
		/// 秒
		uint8  second;
		/// 毫秒
		uint8  milliseconds;
	};
	
	/// 时间
	class WHALE_API WGenericTime : public WObject
	{
	public:
		
		WGenericTime() = default;
		
		WGenericTime(const WGenericTime &) = delete;
	
	public:
		
		WGenericTime &operator=(const WGenericTime &) = delete;
	
	public:
		
		/// 获取系统时间
		virtual void GetSystemTime(FTime &time) const = 0;
		
		/// 获取本地时间
		virtual void GetLocalTime(FTime &time) const = 0;
		
	};
	
} // Whale
