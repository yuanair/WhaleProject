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
	
	/// 调用构造函数
	template<class T, class... Args>
	WHALE_API T *ConstructAt(T *location, Args &&... args) noexcept(
	noexcept(::new(location) T(Whale::Forward<Args>(args)...)))
	{
		return ::new(location) T(Whale::Forward<Args>(args)...);
	}
	
	/// 调用析构函数
	template<class T>
	WHALE_API void DestroyAt(T *location) noexcept(noexcept(location->~T()))
	{
		location->~T();
	}
	
	/// 内存移动
	WHALE_API inline void MemoryMove(void *dest, void *source, SizeT size) noexcept
	{
		::memmove(dest, source, size);
	}
	
	/// 内存拷贝
	WHALE_API inline void MemoryCopy(void *dest, void *source, SizeT size) noexcept
	{
		::memcpy(dest, source, size);
	}
	
	template<class ElemT>
	WHALE_API void Swap(TFAllocator<ElemT> &a, TFAllocator<ElemT> &b) noexcept { a.Swap(b); }
	
} // Whale

#include "TFAllocator.inl"
