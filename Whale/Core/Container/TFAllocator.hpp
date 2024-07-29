//
// Created by admin on 2024/7/28.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"
#include "Whale/Core/Utility.hpp"

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
		
		constexpr TFAllocator() noexcept {} // NOLINT(*-use-equals-default)
		
		constexpr TFAllocator(const TFAllocator &) noexcept = default;
		
		template<class Other>
		constexpr TFAllocator(const TFAllocator<Other> &) noexcept // NOLINT(*-explicit-constructor)
		{}
		
		inline ~TFAllocator() noexcept = default;
	
	public:
		
		inline TFAllocator &operator=(const TFAllocator &) = default;
	
	public:
		
		inline void Deallocate(ElemT *const ptr, const size_t count)
		{
			WHALE_ASSERT(ptr != nullptr || count == 0, L"null pointer cannot point to a block of non-zero size");
			PrivateDeallocate(ptr, sizeof(ElemT) * count);
		}
		
		inline __declspec(allocator) ElemT *Allocate(const size_t count)
		{
			static_assert(sizeof(ElemT) > 0, "ElemT must be complete before calling allocate.");
			return static_cast<ElemT *>(PrivateAllocate(sizeof(ElemT) * count));
		}
	
	private:
		
		static inline __declspec(allocator) void *PrivateAllocate(const size_t bytes)
		{
			return ::operator new(bytes);
		}
		
		static inline void PrivateDeallocate(void *ptr, size_t bytes) noexcept
		{
			::operator delete(ptr, bytes);
		}
	
	private:
		
		ElemT *m_ptr;
		
	};
	
	
} // Whale

#include "TFAllocator.inl"
