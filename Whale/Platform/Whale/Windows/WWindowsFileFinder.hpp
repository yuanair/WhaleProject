//
// Created by admin on 2024/8/13.
//

#pragma once

#include "HWinDef.hpp"
#include "../WGenericFileFinder.hpp"

namespace Whale
{
	
	class WHALE_API WWindowsFileFinder : public WGenericFileFinder
	{
	public:
		
		~WWindowsFileFinder() override;
	
	public:
		
		Bool FindFirst(const FString &string, FFindData &find) override;
		
		Bool FindNext(FFindData &find) override;
		
		Bool Close() override;
	
	private:
		
		HHandle m_handle;
		
	};
	
} // Whale
