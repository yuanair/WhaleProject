
#include "../XMemory.hpp"
#include "../FMath.hpp"

namespace Whale::Container
{
	
	
	template<class ElemT, class AllocatorT>
	TFDynamicArray<ElemT, AllocatorT>::TFDynamicArray(const TFDynamicArray &other)
		: m_allocator(), m_capacity(other.m_length), m_length(other.m_length),
		  m_data(m_allocator.Allocate(m_capacity))
	{
		for (ElemT *curr = m_data, *source = other.m_data, *pEnd = m_data + m_length; curr < pEnd; ++curr, ++source)
		{
			ConstructAt(curr, *source);
		}
	}
	
	template<class ElemT, class AllocatorT>
	TFDynamicArray<ElemT, AllocatorT>::TFDynamicArray(TFDynamicArray &&other) noexcept
		: TFDynamicArray()
	{
		Swap(other);
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
			ConstructAt(curr, *start);
		}
	}
	
	template<class ElemT, class AllocatorT>
	TFDynamicArray<ElemT, AllocatorT>::~TFDynamicArray() noexcept
	{
		DestroyAll();
		m_allocator.Deallocate(m_data, m_capacity);
		m_data     = nullptr;
		m_capacity = 0;
	}
	
	template<class ElemT, class AllocatorT>
	TFDynamicArray<ElemT, AllocatorT> &TFDynamicArray<ElemT, AllocatorT>::operator=(TFDynamicArray other) noexcept
	{
		Swap(other);
		return *this;
	}
	
	template<class ElemT, class AllocatorT>
	TFDynamicArray<ElemT, AllocatorT> &TFDynamicArray<ElemT, AllocatorT>::operator+=(ElemT elem)
	{
		if (m_length >= m_capacity) Expansion();
		ConstructAt(m_data + m_length, Whale::Move(elem));
		++m_length;
		return *this;
	}
	
	template<class ElemT, class AllocatorT>
	ElemT &TFDynamicArray<ElemT, AllocatorT>::operator[](SizeT index)
	{
		WHALE_ASSERT(index < m_length);
		return m_data[index];
	}
	
	template<class ElemT, class AllocatorT>
	const ElemT &TFDynamicArray<ElemT, AllocatorT>::operator[](SizeT index) const
	{
		WHALE_ASSERT(index < m_length);
		return m_data[index];
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
	Bool TFDynamicArray<ElemT, AllocatorT>::Equal(const TFDynamicArray &other) const
	{
		if (m_length != other.m_length) return false;
		for (ElemT *curr = m_data, *oCurr = other.m_data, *pEnd = m_data + m_length; curr < pEnd; ++curr, ++oCurr)
		{
			if (curr->operator!=(*other)) return false;
		}
		return true;
	}
	
	template<class ElemT, class AllocatorT>
	ElemT &TFDynamicArray<ElemT, AllocatorT>::Append(ElemT elem)
	{
		if (m_length >= m_capacity) Expansion();
		ConstructAt(m_data + m_length, Whale::Move(elem));
		return m_data[m_length++];
	}
	
	template<class ElemT, class AllocatorT>
	ElemT TFDynamicArray<ElemT, AllocatorT>::PopBack()
	{
		WHALE_ASSERT(m_length != 0);
		if (m_length != 0) --m_length;
		return Whale::Move(m_data[m_length]);
	}
	
	template<class ElemT, class AllocatorT>
	ElemT &TFDynamicArray<ElemT, AllocatorT>::Insert(ElemT elem, const FConstIterator &where)
	{
		WHALE_ASSERT(IsIn(where));
		if (m_length >= m_capacity) Expansion();
		ConstructAt(m_data + m_length, Whale::Move(elem));
		throw;
	}
	
	template<class ElemT, class AllocatorT>
	void TFDynamicArray<ElemT, AllocatorT>::Clear()
	{
		TFDynamicArray().Swap(*this);
	}
	
	template<class ElemT, class AllocatorT>
	void TFDynamicArray<ElemT, AllocatorT>::DestroyAll()
	{
		for (ElemT *iter = m_data, *pEnd = m_data + m_length; iter < pEnd; ++iter)
		{
			DestroyAt(iter);
		}
		m_length = 0;
	}
	
	template<class ElemT, class AllocatorT>
	void TFDynamicArray<ElemT, AllocatorT>::Erase(const TFDynamicArray::FConstIterator &where)
	{
		WHALE_ASSERT(IsIn(where) && where != end());
		DestroyAt(where.GetPtr());
		for (const ElemT *curr = where.GetPtr(); curr < end(); ++curr)
		{
		
		}
		throw;
	}
	
	template<class ElemT, class AllocatorT>
	void TFDynamicArray<ElemT, AllocatorT>::Erase(const TFDynamicArray::FConstIterator &startIter,
	                                              const TFDynamicArray::FConstIterator &endIter)
	{
		WHALE_ASSERT(IsIn(startIter) && IsIn(endIter));
		throw;
	}
	
	template<class ElemT, class AllocatorT>
	void TFDynamicArray<ElemT, AllocatorT>::AdjustCapacity(Whale::SizeT capacity)
	{
		ElemT *pOldEnd = m_data + m_length;
		/* m_length ^^^ old ^^^ // vvv new vvv */
		m_length = FMath::Min(m_length, capacity);
		
		ElemT *oldData = m_data;
		/* m_data ^^^ old ^^^ // vvv new vvv */
		m_data = m_allocator.Allocate(capacity);
		for (ElemT *curr = oldData + m_length; curr < pOldEnd; ++curr)
		{
			DestroyAt(curr);
		}
		MemoryCopy(m_data, oldData, sizeof(ElemT) * m_length);
		m_allocator.Deallocate(oldData, m_capacity);
		
		/* m_capacity ^^^ old ^^^ // vvv new vvv */
		m_capacity = capacity;
	}
	
	template<class ElemT, class AllocatorT>
	SizeT TFDynamicArray<ElemT, AllocatorT>::CalculateGrowth(SizeT newSize) const
	{
		const SizeT geometric = m_capacity + m_capacity / 2;
		return FMath::Max(geometric, newSize);
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
	template<class... Args>
	void TFDynamicArray<ElemT, AllocatorT>::AdjustLength(SizeT length, Args &&... args)
	{
		if (m_length < length)
		{
			ElemT *curr = m_data + m_length;
			Reserve(length);
			for (ElemT *pEnd = m_data + length; curr < pEnd; ++curr)
			{
				ConstructAt(curr, Whale::Forward<Args>(args)...);
			}
			m_length = length;
		}
		else if (m_length > length)
		{
			for (ElemT *curr = m_data + length, *pEnd = m_data + m_length; curr < pEnd; ++curr)
			{
				DestroyAt(curr);
			}
			m_length = length;
		}
	}
	
	template<class ElemT, class AllocatorT>
	template<class IterT>
	void TFDynamicArray<ElemT, AllocatorT>::CopyFrom(const IterT &beginIt, const IterT &endIt)
	{
		DestroyAll();
		for (IterT iter = beginIt; iter != endIt; ++iter)
		{
			Append(*iter);
		}
	}
	
}
