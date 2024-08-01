//
// Created by admin on 2024/8/1.
//

#pragma once

#include <Whale/Container/TFString.hpp>
#include "HWinDef.hpp"
#include "FResult.hpp"

namespace Whale::Win32
{
	
	/// PE文件格式
	class WHALE_API FPE
	{
	public:
		
		FPE();
		
		~FPE() noexcept;
	
	public:
		
		///
		/// 从文件加载
		/// \tparam ElemT
		/// \param hFile
		template<class ElemT>
		FResult LoadFromFile(HHandle hFile);
		
		/// 销毁
		void Destroy();
	
	public:
		
		[[nodiscard]]const HHandle &GetImageBase() const noexcept { return m_imageBase; }
	
	private:
		
		HHandle m_imageBase;
		HHandle m_hMapping;
		
	};
	
	
} // Whale
