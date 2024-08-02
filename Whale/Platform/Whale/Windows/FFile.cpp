//
// Created by admin on 2024/8/1.
//

#include "FFile.hpp"

#include <windows.h>

namespace Whale::Windows
{
	
	
	template<>
	WHALE_API HHandle FFile::OpenReadOnly(const StringA &fileName)
	{
		return {
			::CreateFileA(
				fileName.CStr(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr
			)
		};
	}
	
	template<>
	WHALE_API HHandle FFile::OpenReadOnly(const StringW &fileName)
	{
		return {
			::CreateFileW(
				fileName.CStr(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr
			)
		};
	}
	
	template<>
	WHALE_API HHandle FFile::OpenWriteOnly(const StringA &fileName)
	{
		return {
			::CreateFileA(
				fileName.CStr(), GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr
			)
		};
	}
	
	template<>
	WHALE_API HHandle FFile::OpenWriteOnly(const StringW &fileName)
	{
		return {
			::CreateFileW(
				fileName.CStr(), GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr
			)
		};
	}
	
} // Whale