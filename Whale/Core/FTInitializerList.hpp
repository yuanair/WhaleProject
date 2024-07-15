//
// Created by admin on 2024/7/15.
//

#pragma once

#include "FTypeDef.hpp"

namespace Whale
{
	
	///
	/// 初始化列表
	/// \tparam ElemT 元素类型
	template<class ElemT>
	class FTInitializerList
	{
	public:
		using ValueType = ElemT;
		using Reference = const ElemT &;
		using ConstReference = const ElemT &;
		
		using Iterator = const ElemT *;
		using ConstIterator = const ElemT *;
		
		constexpr FTInitializerList() noexcept: first(nullptr), last(nullptr) {}
		
		constexpr FTInitializerList(const ElemT *first, const ElemT *last) noexcept
			: first(first), last(last) {}
		
		constexpr const ElemT *Begin() const noexcept
		{
			return first;
		}
		
		constexpr const ElemT *End() const noexcept
		{
			return last;
		}
		
		/// for foreach
		constexpr const ElemT *begin() const noexcept { return Begin(); }
		
		/// for foreach
		constexpr const ElemT *end() const noexcept { return End(); }
		
		[[nodiscard]]
		constexpr SizeT Size() const noexcept
		{
			return static_cast<SizeT>(last - first);
		}
	
	private:
		const ElemT *first;
		const ElemT *last;
	};
	
} // Whale
