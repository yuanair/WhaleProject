//
// Created by admin on 2024/7/1.
//

#pragma once

#include <Whale/Container/TFString.hpp>
#include <Whale/TypeDef.hpp>
#include "HWinDef.hpp"

namespace Whale::Win32
{
	
	///
	/// 消息框返回值
	///
	enum FMessageBoxResult
	{
		FMessageBoxResultNull     = 0,
		FMessageBoxResultOK       = 1,
		FMessageBoxResultCancel   = 2,
		FMessageBoxResultAbort    = 3,
		FMessageBoxResultRetry    = 4,
		FMessageBoxResultIgnore   = 5,
		FMessageBoxResultYes      = 6,
		FMessageBoxResultNo       = 7,
		FMessageBoxResultTryAgain = 10,
		FMessageBoxResultContinue = 11
	};
	
	///
	/// 消息框类型
	///
	enum FMessageBoxType : uint32
	{
		FMessageBoxTypeOK                = 0x00000000L,
		FMessageBoxTypeOKCancel          = 0x00000001L,
		FMessageBoxTypeAbortRetryIgnore  = 0x00000002L,
		FMessageBoxTypeYesNoCancel       = 0x00000003L,
		FMessageBoxTypeYesNo             = 0x00000004L,
		FMessageBoxTypeRetryCancel       = 0x00000005L,
		FMessageBoxTypeCancelTryContinue = 0x00000006L,
		
		FMessageBoxIconNull     = 0x00000000L,
		FMessageBoxIconUser     = 0x00000080L,
		FMessageBoxIconInfo     = 0x00000040L,
		FMessageBoxIconQuestion = 0x00000020L,
		FMessageBoxIconWarning  = 0x00000030L,
		FMessageBoxIconError    = 0x00000010L,
		FMessageBoxIconStop     = 0x00000010L,
		
		FMessageBoxButton1 = 0x00000000L,
		FMessageBoxButton2 = 0x00000100L,
		FMessageBoxButton3 = 0x00000200L,
		FMessageBoxButton4 = 0x00000300L
	};
	
	// 消息框
	class WHALE_API FMessageBox
	{
	public:
		
		// 显示消息框
		static FMessageBoxResult Show(const StringA &message, const StringA &caption,
		                              uint32 type = FMessageBoxTypeOK | FMessageBoxIconNull | FMessageBoxButton1);
		
		// 显示消息框
		static FMessageBoxResult Show(const StringW &message, const StringW &caption,
		                              uint32 type = FMessageBoxTypeOK | FMessageBoxIconNull | FMessageBoxButton1);
		
	};
	
} // Whale
