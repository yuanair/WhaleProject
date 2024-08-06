//
// Created by admin on 2024/7/28.
//

#pragma once

#include "../TypeDef.hpp"
#include "../Utility.hpp"

namespace Whale::Container
{
	
	///
	/// 内存分配器
	template<class ElemT>
	class TFAllocator
	{
	public:
		
		static_assert(
			!std::is_const_v<ElemT>, "Forbids containers of const elements "
			                         "because TFAllocator<const T> is ill-formed."
		);
	
	public:
		
		inline ElemT *Allocate(SizeT count) noexcept;
		
		inline void Deallocate(ElemT *ptr, SizeT count) noexcept;
		
		inline void Swap(TFAllocator &other) noexcept {}
	
	private:
		
		static inline void *PrivateAllocate(SizeT bytes) noexcept;
		
		static inline void PrivateDeallocate(void *ptr, SizeT bytes) noexcept;
		
	};
	
	template<class ElemT>
	void WHALE_API Swap(TFAllocator<ElemT> &a, TFAllocator<ElemT> &b) noexcept { a.Swap(b); }
	
} // Whale

#include "TFAllocator.inl"
