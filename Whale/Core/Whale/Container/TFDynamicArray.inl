
namespace Whale::Container
{
	
	
	template<class ElemT, class AllocatorT>
	TFDynamicArray<ElemT, AllocatorT>::TFDynamicArray(const TFDynamicArray &other)
		: m_allocator(), m_capacity(other.m_capacity), m_length(other.m_length),
		  m_data(m_allocator.Allocate(m_capacity))
	{
		for (ElemT *curr = m_data, *source = other.m_data, *pEnd = m_data + m_length; curr < pEnd; ++curr, ++source)
		{
			*curr = *source;
		}
	}
	
	template<class ElemT, class AllocatorT>
	TFDynamicArray<ElemT, AllocatorT>::TFDynamicArray(TFDynamicArray &&other) noexcept
		: m_allocator(), m_capacity(other.m_capacity), m_length(other.m_length),
		  m_data(m_allocator.Allocate(m_capacity))
	{
		for (ElemT *curr = m_data, *source = other.m_data, *pEnd = m_data + m_length; curr < pEnd; ++curr, ++source)
		{
			*curr = Whale::Move(*source);
		}
	}
	
	template<class ElemT, class AllocatorT>
	TFDynamicArray<ElemT, AllocatorT>::TFDynamicArray(SizeT capacity) noexcept
		: m_allocator(), m_capacity(capacity), m_length(0),
		  m_data(m_allocator.Allocate(m_capacity))
	{
	
	}
	
	template<class ElemT, class AllocatorT>
	TFDynamicArray<ElemT, AllocatorT>::TFDynamicArray(const ElemT *start, const ElemT *end)
		: m_allocator(), m_capacity(end - start), m_length(m_capacity),
		  m_data(m_allocator.Allocate(m_capacity))
	{
		WHALE_ASSERT(start <= end);
		for (ElemT *curr = m_data; start < end; ++curr, ++start)
		{
			*curr = *start;
		}
	}
	
	template<class ElemT, class AllocatorT>
	TFDynamicArray<ElemT, AllocatorT>::~TFDynamicArray() noexcept
	{
		for (ElemT *iter = m_data, *pEnd = m_data + m_length; iter < pEnd; ++iter)
		{
			iter->~ElemT();
		}
		m_allocator.Deallocate(m_data, m_capacity);
		m_data     = nullptr;
		m_length   = 0;
		m_capacity = 0;
	}
	
	template<class ElemT, class AllocatorT>
	TFDynamicArray<ElemT, AllocatorT> &TFDynamicArray<ElemT, AllocatorT>::operator=(TFDynamicArray other) noexcept
	{
		Swap(other);
		return *this;
	}
	
	template<class ElemT, class AllocatorT>
	ElemT &TFDynamicArray<ElemT, AllocatorT>::At(SizeT index)
	{
		WHALE_ASSERT(index < m_length);
		return m_data[index];
	}
	
	template<class ElemT, class AllocatorT>
	ElemT &TFDynamicArray<ElemT, AllocatorT>::At(SizeT index) const
	{
		WHALE_ASSERT(index < m_length);
		return m_data[index];
	}
	
	template<class ElemT, class AllocatorT>
	ElemT &TFDynamicArray<ElemT, AllocatorT>::Append(ElemT elem)
	{
		if (m_length == m_capacity) Expansion();
		return m_data[m_length++] = Whale::Move(elem);
	}
	
	template<class ElemT, class AllocatorT>
	SizeT TFDynamicArray<ElemT, AllocatorT>::CalculateGrowth(SizeT newSize) const
	{
		const SizeT oldCapacity = GetCapacity();
		const SizeT geometric   = oldCapacity + oldCapacity / 2;
		if (geometric < newSize) return newSize;
		return geometric;
	}
	
	template<class ElemT, class AllocatorT>
	void TFDynamicArray<ElemT, AllocatorT>::Expansion()
	{
		ElemT *oldData    = m_data;
		ElemT *oldEnd     = m_data + m_length;
		SizeT oldCapacity = m_capacity;
		m_capacity = CalculateGrowth(m_capacity + 1);
		m_data     = m_allocator.Allocate(m_capacity);
		for (ElemT *curr = m_data, *source = oldData; source < oldEnd; ++source, ++curr)
		{
			*curr = Whale::Move(*source);
		}
		m_allocator.Deallocate(oldData, oldCapacity);
	}
	
	template<class ElemT, class AllocatorT>
	void TFDynamicArray<ElemT, AllocatorT>::Swap(TFDynamicArray &other) noexcept
	{
		if (this == &other) return;
		using Whale::Swap;
		Swap(m_allocator, other.m_allocator);
		Swap(m_capacity, other.m_capacity);
		Swap(m_length, other.m_length);
		Swap(m_data, other.m_data);
	}
	
	template<class ElemT, class AllocatorT>
	template<class IterT>
	void TFDynamicArray<ElemT, AllocatorT>::CopyFrom(const IterT &beginIt, const IterT &endIt)
	{
		for (ElemT *iter = m_data, *pEnd = m_data + m_length; iter < pEnd; ++iter)
		{
			iter->~ElemT();
		}
		m_length = 0;
		for (IterT iter = beginIt; iter != endIt; ++iter)
		{
			Append(*iter);
		}
	}
	
}
