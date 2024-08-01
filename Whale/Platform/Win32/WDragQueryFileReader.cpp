//
// Created by admin on 2024/7/31.
//

#include "WDragQueryFileReader.hpp"
#include <windows.h>

namespace Whale::Win32
{
	
	template<>
	WHALE_API void WDragQueryFileReader::Init<CharA>(HDrop hDrop) noexcept
	{
		Destroy();
		m_hDrop     = hDrop;
		m_fileCount = ::DragQueryFileA((HDROP) hDrop.handle, (UINT) -1, nullptr, 0);
	}
	
	template<>
	WHALE_API void WDragQueryFileReader::Init<CharW>(HDrop hDrop) noexcept
	{
		Destroy();
		m_hDrop     = hDrop;
		m_fileCount = ::DragQueryFileW((HDROP) hDrop.handle, (UINT) -1, nullptr, 0);
	}
	
	void WDragQueryFileReader::Destroy() noexcept
	{
		if (m_hDrop.handle) ::DragFinish((HDROP) m_hDrop.handle);
		m_hDrop.handle = nullptr;
	}
	
	template<>
	WHALE_API Bool WDragQueryFileReader::Get(StringA &fileName, uint32 index) noexcept
	{
		if (index >= m_fileCount) return false;
		UINT length = ::DragQueryFileA((HDROP) m_hDrop.handle, (UINT) index, nullptr, 0) + 1;
		auto buffer = new CharA[length];
		if (!::DragQueryFileA((HDROP) m_hDrop.handle, (UINT) index, buffer, length))
		{
			delete[] buffer;
			return false;
		}
		fileName = buffer;
		delete[] buffer;
		return true;
	}
	
	template<>
	WHALE_API Bool WDragQueryFileReader::Get(StringW &fileName, uint32 index) noexcept
	{
		if (index >= m_fileCount) return false;
		UINT length = ::DragQueryFileW((HDROP) m_hDrop.handle, (UINT) index, nullptr, 0) + 1;
		auto buffer = new CharW[length];
		if (!::DragQueryFileW((HDROP) m_hDrop.handle, (UINT) index, buffer, length))
		{
			delete[] buffer;
			return false;
		}
		fileName = buffer;
		delete[] buffer;
		return true;
	}
	
	
} // Whale