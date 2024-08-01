//
// Created by admin on 2024/8/1.
//

#pragma once

#include "HWinDef.hpp"
#include <Whale/Container/TFString.hpp>

namespace Whale::Win32
{
	
	/// 文件
	class WHALE_API FFile
	{
	public:
		
		///
		/// 打开文件（只读）
		/// \tparam ElemT
		/// \param fileName 文件名
		/// \return 文件
		template<class ElemT>
		static HHandle OpenReadOnly(const Container::TFString<ElemT> &fileName);
		
		///
		/// 打开文件（只写）
		/// \tparam ElemT
		/// \param fileName 文件名
		/// \return 文件
		template<class ElemT>
		static HHandle OpenWriteOnly(const Container::TFString<ElemT> &fileName);
		
	};
	
	
} // Whale
