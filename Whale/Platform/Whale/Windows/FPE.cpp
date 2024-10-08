//
// Created by admin on 2024/8/1.
//

#include "FPE.hpp"
#include "FCore.hpp"

#include "Whale/FDebug.hpp"
#include "WWindowsFile.hpp"
#include <windows.h>

namespace Whale
{
	FPE::FPE() = default;
	
	FPE::~FPE() noexcept
	{
		Destroy();
	}
	
	template<>
	WHALE_API FResult FPE::LoadFromFile<CharA>(WGenericFile *pFile)
	{
		Destroy();
		auto *pWinFile = dynamic_cast<WWindowsFile *>(pFile);
		if (pWinFile == nullptr) return E_INVALIDARG;
		m_hMapping.handle = CreateFileMappingA(pWinFile->GetHandle().handle, nullptr, PAGE_READONLY, 0, 0, nullptr);
		if (!m_hMapping.handle)
		{
			return FCore::GetLastError();
		}
		
		m_imageBase.handle = MapViewOfFile(m_hMapping.handle, FILE_MAP_READ, 0, 0, 0);
		if (!m_imageBase.handle)
		{
			Destroy();
			FDebug::Log<Char>(Error, logTag, WTEXT("文件映射错误"));
			return FCore::GetLastError();
		}
		return S_OK;
	}
	
	
	template<>
	WHALE_API FResult FPE::LoadFromFile<CharW>(WGenericFile *pFile)
	{
		Destroy();
		auto *pWinFile = dynamic_cast<WWindowsFile *>(pFile);
		if (pWinFile == nullptr) return E_INVALIDARG;
		m_hMapping.handle = CreateFileMappingW(pWinFile->GetHandle().handle, nullptr, PAGE_READONLY, 0, 0, nullptr);
		if (!m_hMapping.handle)
		{
			return FCore::GetLastError();
		}
		
		m_imageBase.handle = MapViewOfFile(m_hMapping.handle, FILE_MAP_READ, 0, 0, 0);
		if (!m_imageBase.handle)
		{
			Destroy();
			FDebug::Log<Char>(Error, logTag, WTEXT("文件映射错误"));
			return FCore::GetLastError();
		}
		return S_OK;
	}
	
	void FPE::Destroy()
	{
		if (m_imageBase.handle) UnmapViewOfFile(m_imageBase.handle);
		m_imageBase.handle = nullptr;
		if (m_hMapping.handle) CloseHandle(m_hMapping.handle);
		m_hMapping.handle = nullptr;
		
	}
	
	
} // Whale