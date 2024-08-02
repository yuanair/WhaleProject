//
// Created by admin on 2024/8/2.
//

#pragma once

#include "Whale/WGenericPlatform.hpp"
#include "HWinDef.hpp"

namespace Whale
{
	
	/// Windows
	class WHALE_API WWindowsPlatform : public WGenericPlatform
	{
	public:
		
		void Exit(int32 result) const override;
		
		[[nodiscard]] FString GetName() const override;
		
		[[nodiscard]] Bool IsRunAsAdministrator() const override;
		
		[[nodiscard]] HModule GetModuleHandle() const override;
		
	};
	
	typedef WWindowsPlatform WPlatform;
	
} // Whale
