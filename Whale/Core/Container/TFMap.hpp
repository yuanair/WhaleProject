//
// Created by admin on 2024/7/23.
//

#pragma once

#include "Whale/Core/Utility.hpp"
#include "Whale/Core/CRT.hpp"
#include "TFTree.hpp"
#include "TFPair.hpp"
#include "InitList.hpp"

namespace Whale::Container
{
	
	///
	/// 表
	/// \tparam KeyT
	/// \tparam ValueT
	template<class KeyT, class ValueT>
	class WHALE_API TFMap
	{
	public:
		
		TFMap() noexcept = default;
		
		~TFMap() noexcept = default;
	
	public:
	
	
	private:
		
		TFTree<TFPair<KeyT, ValueT>> m_tree;
		
	};
	
} // Whale
