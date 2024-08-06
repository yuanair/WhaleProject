

namespace Whale::Container
{
	template<class ElemT>
	ElemT *TFAllocator<ElemT>::Allocate(SizeT count) noexcept
	{
		static_assert(sizeof(ElemT) > 0, "ElemT must be complete before calling allocate.");
		return static_cast<ElemT *>(PrivateAllocate(sizeof(ElemT) * count));
	}
	
	template<class ElemT>
	void TFAllocator<ElemT>::Deallocate(ElemT *ptr, SizeT count) noexcept
	{
		WHALE_ASSERT(ptr != nullptr || count == 0);
		PrivateDeallocate(ptr, sizeof(ElemT) * count);
	}
	
	template<class ElemT>
	void *TFAllocator<ElemT>::PrivateAllocate(SizeT bytes) noexcept
	{
		return ::operator new(bytes);
	}
	
	template<class ElemT>
	void TFAllocator<ElemT>::PrivateDeallocate(void *ptr, SizeT bytes) noexcept
	{
		::operator delete(ptr, bytes);
	}
	
}

