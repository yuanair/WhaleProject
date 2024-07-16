//
// Created by admin on 2024/7/1.
//


#include <windows.h>

#include "FMessageBox.hpp"

namespace Whale::Win32
{
	
	FMessageBoxResult FMessageBox::Show(const FTStringA &message, const FTStringA &caption, uint32 type)
	{
		return (FMessageBoxResult) ::MessageBoxA(nullptr, message.CStr(), caption.CStr(), type);
	}
	
	FMessageBoxResult FMessageBox::Show(const FTStringW &message, const FTStringW &caption, uint32 type)
	{
		return (FMessageBoxResult) ::MessageBoxW(nullptr, message.CStr(), caption.CStr(), type);
	}
	
	FMessageBoxResult FMessageBox::Show(const FTStringA &message, uint32 type)
	{
		return (FMessageBoxResult) ::MessageBoxA(nullptr, message.CStr(), defaultCaptionA.CStr(), type);
	}
	
	FMessageBoxResult FMessageBox::Show(const FTStringW &message, uint32 type)
	{
		return (FMessageBoxResult) ::MessageBoxW(nullptr, message.CStr(), defaultCaptionW.CStr(), type);
	}
	
	FTStringA FMessageBox::defaultCaptionA{"Whale"};
	FTStringW FMessageBox::defaultCaptionW{L"Whale"};
	
	
} // Whale