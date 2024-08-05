//
// Created by admin on 2024/8/5.
//

#pragma once

#include "../Utility.hpp"
#include "TIIterator.hpp"

namespace Whale
{
	
	template<class ElemT>
	class WHALE_API TIPointerIterator : public TIIterator<ElemT>
	{
	public:
		
		explicit TIPointerIterator(ElemT *ptr) : ptr(ptr) {}
	
	public:
		
		TIPointerIterator &operator++();
		
		TIPointerIterator operator++(int);
		
		TIPointerIterator &operator--();
		
		TIPointerIterator operator--(int);
		
		Bool operator==(const TIPointerIterator &other) const;
		
		Bool operator!=(const TIPointerIterator &other) const;
		
		ElemT &operator*();
	
	private:
		
		ElemT *ptr;
		
	};
	
	template<class ElemT>
	TIPointerIterator<ElemT> &TIPointerIterator<ElemT>::operator++()
	{
		++ptr;
		return *this;
	}
	
	template<class ElemT>
	TIPointerIterator<ElemT> TIPointerIterator<ElemT>::operator++(int)
	{
		TIPointerIterator iterator = *this;
		++(*this);
		return iterator;
	}
	
	template<class ElemT>
	TIPointerIterator<ElemT> &TIPointerIterator<ElemT>::operator--()
	{
		--ptr;
		return *this;
	}
	
	template<class ElemT>
	TIPointerIterator<ElemT> TIPointerIterator<ElemT>::operator--(int)
	{
		TIPointerIterator iterator = *this;
		--(*this);
		return iterator;
	}
	
	template<class ElemT>
	Bool TIPointerIterator<ElemT>::operator==(const TIPointerIterator &other) const
	{
		return ptr == other.ptr;
	}
	
	template<class ElemT>
	Bool TIPointerIterator<ElemT>::operator!=(const TIPointerIterator &other) const
	{
		return ptr != other.ptr;
	}
	
	template<class ElemT>
	ElemT &TIPointerIterator<ElemT>::operator*()
	{
		return *ptr;
	}
	
} // Whale
