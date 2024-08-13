//
// Created by admin on 2024/8/4.
//

#pragma once

#include "HWinDef.hpp"

#include "../WGenericTime.hpp"

struct _SYSTEMTIME; // NOLINT(*-reserved-identifier)
typedef _SYSTEMTIME SYSTEMTIME;
struct _FILETIME; // NOLINT(*-reserved-identifier)
typedef _FILETIME FILETIME;

namespace Whale
{
	
	
	class WHALE_API WWindowsTime : public WGenericTime
	{
	public:
		
		static WWindowsTime &Get();
		
		static void SystemTimeToFTime(FTime &fTime, const ::SYSTEMTIME &systemTime);
		
		static void FTimeToSystemTime(::SYSTEMTIME &systemTime, const class FTime &fTime);
		
		static Bool FileTimeToFTime(FTime &fTime, const ::FILETIME &fileTime);
		
		static Bool FTimeToFileTime(::FILETIME &fileTime, const class FTime &fTime);
	
	public:
		
		void GetSystemTime(FTime &time) const override;
		
		void GetLocalTime(FTime &time) const override;
	
	private:
		
		WWindowsTime() = default;
		
	};
	
} // Whale
