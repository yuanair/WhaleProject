//
// Created by admin on 2024/8/5.
//

#pragma once

#include "../Utility.hpp"
#include "TIIterator.hpp"

namespace Whale::Container
{
	/// 范围
	template<class ElemT, ElemT Start, ElemT End>
	class WHALE_API TFRange
	{
	public:
		
		class FIterator : public TIIterator<ElemT>
		{
		public:
			
			explicit FIterator(ElemT m_num) : m_num(m_num) {}
		
		public:
			
			TIIterator<ElemT> &operator++();
			
			TIIterator<ElemT> operator++(int);
			
			Bool operator==(const FIterator &other) const;
			
			Bool operator!=(const FIterator &other) const;
			
			const ElemT &operator*() const;
		
		private:
			
			ElemT m_num;
			
		};
	
	public:
		
		FIterator begin() const { return FIterator(Start); }
		
		FIterator end() const { return FIterator(End); }
		
	};
	
	template<class ElemT, ElemT Start, ElemT End>
	TIIterator<ElemT> &TFRange<ElemT, Start, End>::FIterator::operator++()
	{
		if constexpr (End >= Start) ++m_num;
		else --m_num;
		return *this;
	}
	
	template<class ElemT, ElemT Start, ElemT End>
	TIIterator<ElemT> TFRange<ElemT, Start, End>::FIterator::operator++(int)
	{
		TIIterator<ElemT> result = *this;
		++(*this);
		return result;
	}
	
	template<class ElemT, ElemT Start, ElemT End>
	Bool TFRange<ElemT, Start, End>::FIterator::operator==(const TFRange::FIterator &other) const
	{
		return m_num == other.m_num;
	}
	
	template<class ElemT, ElemT Start, ElemT End>
	Bool TFRange<ElemT, Start, End>::FIterator::operator!=(const TFRange::FIterator &other) const
	{
		return m_num != other.m_num;
	}
	
	template<class ElemT, ElemT Start, ElemT End>
	const ElemT &TFRange<ElemT, Start, End>::FIterator::operator*() const
	{
		return m_num;
	}
	
} // Whale
