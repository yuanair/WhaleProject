//
// Created by admin on 2024/8/2.
//

#pragma once

#include "HWinDef.hpp"
#include "../WGenericFile.hpp"

namespace Whale
{
	
	class WHALE_API WWindowsFile : public WGenericFile
	{
	public:
		
		void Open(const FString &fileName, EFileOpenMode openMode) override;
		
		void Close() override;
	
	public:
		
		[[nodiscard]] const HHandle &GetHandle() const noexcept { return m_handle; }
	
	private:
		
		HHandle m_handle;
		
	};
	
	typedef WWindowsFile WFile;
	
} // Whale
