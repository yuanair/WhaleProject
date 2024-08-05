//
// Created by admin on 2024/8/5.
//

#pragma once

#include "../Utility.hpp"
#include "TIIterator.hpp"

namespace Whale
{
	
	template<class Base>
	class WHALE_API TFReverseIterator : TIIterator<Base>
	{
	public:
		
		explicit TFReverseIterator(Base base) : m_base(base) {}
	
	public:
		
		TFReverseIterator &operator++();
		
		TFReverseIterator operator++(int);
		
		TFReverseIterator &operator--();
		
		TFReverseIterator operator--(int);
		
		Bool operator==(const TFReverseIterator &other) const;
		
		Bool operator!=(const TFReverseIterator &other) const;
		
		auto &operator*();
	
	public:
		
		[[nodiscard]]Base GetBase() const { return m_base; }
	
	private:
		
		Base m_base;
		
	};
	
	template<class Base>
	TFReverseIterator<Base> &TFReverseIterator<Base>::operator++()
	{
		--m_base;
		return *this;
	}
	
	template<class Base>
	TFReverseIterator<Base> TFReverseIterator<Base>::operator++(int)
	{
		TFReverseIterator<Base> result = *this;
		++(*this);
		return *this;
	}
	
	template<class Base>
	TFReverseIterator<Base> &TFReverseIterator<Base>::operator--()
	{
		++m_base;
		return *this;
	}
	
	template<class Base>
	TFReverseIterator<Base> TFReverseIterator<Base>::operator--(int)
	{
		TFReverseIterator<Base> result = *this;
		--(*this);
		return *this;
	}
	
	template<class Base>
	Bool TFReverseIterator<Base>::operator==(const TFReverseIterator &other) const
	{
		return m_base == other.m_base;
	}
	
	template<class Base>
	Bool TFReverseIterator<Base>::operator!=(const TFReverseIterator &other) const
	{
		return m_base != other.m_base;
	}
	
	template<class Base>
	auto &TFReverseIterator<Base>::operator*()
	{
		return *m_base;
	}
	
} // Whale
