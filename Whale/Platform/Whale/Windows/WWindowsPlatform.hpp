//
// Created by admin on 2024/8/2.
//

#pragma once

#include "Whale/WGenericPlatform.hpp"
#include "HWinDef.hpp"

namespace Whale
{
	
	class WHALE_API WWindowsPlatform : public WGenericPlatform
	{
	public:
		
		static WWindowsPlatform &Get();
	
	public:
		
		[[nodiscard]] int32 Run(WProgram &program) const override;
		
		void Exit(int32 result) const override;
		
		[[nodiscard]] FString GetName() const override;
		
		[[nodiscard]] FString GetVersion() const override;
		
		[[nodiscard]] FString GetNewLine() const override;
		
		[[nodiscard]] Bool IsRunAsAdministrator() const override;
		
		[[nodiscard]] HModule GetModuleHandle() const override;
		
		[[nodiscard]] WGenericWindowManager &GetWindowManager() const override;
		
		[[nodiscard]] WGenericFileManager &GetFileManager() const override;
		
		[[nodiscard]] WGenericLocale &GetLocale() const override;
		
		[[nodiscard]] WGenericTime &GetTime() const override;
		
		[[nodiscard]] WGenericTimer *NewTimer() const override;
	
	private:
		
		WWindowsPlatform() = default;
		
	};
	
	typedef WWindowsPlatform WPlatform;
	
} // Whale
