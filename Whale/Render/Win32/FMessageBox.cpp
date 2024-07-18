//
// Created by admin on 2024/7/1.
//


#include <windows.h>

#include "FMessageBox.hpp"

namespace Whale::Win32
{
	
	FMessageBoxResult FMessageBox::Show(const StringA &message, const StringA &caption, uint32 type)
	{
		return (FMessageBoxResult) ::MessageBoxA(nullptr, message.CStr(), caption.CStr(), type);
	}
	
	FMessageBoxResult FMessageBox::Show(const StringW &message, const StringW &caption, uint32 type)
	{
		return (FMessageBoxResult) ::MessageBoxW(nullptr, message.CStr(), caption.CStr(), type);
	}
	
	
} // Whale