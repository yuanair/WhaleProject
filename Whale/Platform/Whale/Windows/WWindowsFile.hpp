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
		
		WWindowsFile();
		
		WWindowsFile(const FString &fileName, EFileOpenMode openMode, EFileSharedMode sharedMode,
		             EFileCreateMode createMode);
		
		~WWindowsFile() override;
	
	public:
		
		[[nodiscard]] Bool IsOpened() const override;
		
		void Open(
			const FString &fileName, EFileOpenMode openMode,
			EFileSharedMode sharedMode,
			EFileCreateMode createMode
		) override;
		
		void Open(
			const StringA &fileName, EFileOpenMode openMode,
			EFileSharedMode sharedMode,
			EFileCreateMode createMode
		) override;
		
		Bool Write(Char ch) override;
		
		Bool Write(const FString &str) override;
		
		Bool WriteLine() override;
		
		Bool WriteLine(const FString &str) override;
		
		Bool Write(CharA ch) override;
		
		Bool Write(const StringA &str) override;
		
		Bool WriteLine(const StringA &str) override;
		
		Bool Read(Char &ch) override;
		
		Bool Read(FString &str) override;
		
		Bool Read(CharA &ch) override;
		
		Bool Read(StringA &str) override;
		
		Bool SetPosToBegin() override;
		
		Bool SetPosToEnd() override;
		
		Bool Flush() override;
		
		void Close() override;
	
	public:
		
		[[nodiscard]] const HHandle &GetHandle() const noexcept { return m_handle; }
	
	private:
		
		HHandle m_handle;
		
	};
	
} // Whale
