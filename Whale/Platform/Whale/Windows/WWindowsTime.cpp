//
// Created by admin on 2024/8/4.
//

#include "WWindowsTime.hpp"

#include <Windows.h>

namespace Whale
{
	
	void SystemTimeToFTime(FTime &fTime, const ::SYSTEMTIME &systemTime);
	
	void SystemTimeToFTime(::SYSTEMTIME &systemTime, const class FTime &fTime);
	
	WWindowsTime &WWindowsTime::Get()
	{
		static WWindowsTime windowsTime;
		return windowsTime;
	}
	
	void SystemTimeToFTime(FTime &fTime, const ::SYSTEMTIME &systemTime)
	{
		fTime.year         = systemTime.wYear;
		fTime.month        = systemTime.wMonth;
		fTime.dayOfWeek    = systemTime.wDayOfWeek;
		fTime.day          = systemTime.wDay;
		fTime.hour         = systemTime.wHour;
		fTime.minute       = systemTime.wMinute;
		fTime.second       = systemTime.wSecond;
		fTime.milliseconds = systemTime.wMilliseconds;
	}
	
	void SystemTimeToFTime(::SYSTEMTIME &systemTime, const FTime &fTime)
	{
		systemTime.wYear         = fTime.year;
		systemTime.wMonth        = fTime.month;
		systemTime.wDayOfWeek    = fTime.dayOfWeek;
		systemTime.wDay          = fTime.day;
		systemTime.wHour         = fTime.hour;
		systemTime.wMinute       = fTime.minute;
		systemTime.wSecond       = fTime.second;
		systemTime.wMilliseconds = fTime.milliseconds;
	}
	
	void WWindowsTime::GetSystemTime(FTime &time) const
	{
		SYSTEMTIME systemTime;
		::GetSystemTime(&systemTime);
		SystemTimeToFTime(time, systemTime);
	}
	
	void WWindowsTime::GetLocalTime(FTime &time) const
	{
		SYSTEMTIME systemTime;
		::GetSystemTime(&systemTime);
		SystemTimeToFTime(time, systemTime);
	}
} // Whale