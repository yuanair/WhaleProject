//
// Created by admin on 2024/8/1.
//

#pragma once

#include <Whale/Container/TFString.hpp>
#include "HWinDef.hpp"
#include "FResult.hpp"
#include "../WGenericFile.hpp"

namespace Whale
{
	
	/// PE文件格式
	class WHALE_API FPE
	{
	public:
		
		FPE();
		
		~FPE() noexcept;
	
	public:
		
		static constexpr Char logTag[] = WTEXT("WhalePlatform::PE");
	
	public:
		
		///
		/// 从文件加载
		/// \tparam ElemT
		/// \param pFile
		template<class ElemT>
		FResult LoadFromFile(WGenericFile *pFile);
		
		/// 销毁
		void Destroy();
	
	public:
		
		[[nodiscard]]const HHandle &GetImageBase() const noexcept { return m_imageBase; }
	
	private:
		
		HHandle m_imageBase;
		HHandle m_hMapping;
		
	};
	
	
} // Whale
