//
// Created by admin on 2024/8/5.
//

#pragma once

#include "../Utility.hpp"
#include "TIIterator.hpp"

namespace Whale::Container
{
	
	template<class Base, class OffsetT>
	class WHALE_API TFReverseIterator : TIIterator<Base>
	{
	public:
		
		using OffsetType = OffsetT;
	
	public:
		
		explicit TFReverseIterator(Base base) : m_base(Whale::Move(base)) {}
	
	public:
		
		TFReverseIterator &operator++() noexcept;
		
		TFReverseIterator operator++(int) noexcept;
		
		TFReverseIterator &operator--() noexcept;
		
		TFReverseIterator operator--(int) noexcept;
		
		TFReverseIterator &operator+=(OffsetT offset) noexcept;
		
		TFReverseIterator operator+(OffsetT offset) const noexcept;
		
		TFReverseIterator &operator-=(OffsetT offset) noexcept;
		
		TFReverseIterator operator-(OffsetT offset) const noexcept;
		
		OffsetT operator+(const TFReverseIterator &other) const noexcept;
		
		OffsetT operator-(const TFReverseIterator &other) const noexcept;
		
		Bool operator==(const TFReverseIterator &other) const noexcept;
		
		Bool operator!=(const TFReverseIterator &other) const noexcept;
		
		std::strong_ordering operator<=>(const TFReverseIterator &other) const noexcept;
		
		auto &operator*() noexcept;
		
		auto &operator[](OffsetT offset) noexcept;
		
		auto *operator->() noexcept;
		
		auto &operator*() const noexcept;
		
		auto &operator[](OffsetT offset) const noexcept;
		
		auto *operator->() const noexcept;
	
	public:
		
		[[nodiscard]] auto *GetPtr() const { return m_base.GetPtr(); }
		
		[[nodiscard]]Base GetBase() const { return m_base; }
	
	private:
		
		Base m_base;
		
	};
	
	template<class Base, class OffsetT>
	TFReverseIterator<Base, OffsetT> &TFReverseIterator<Base, OffsetT>::operator++() noexcept
	{
		--m_base;
		return *this;
	}
	
	template<class Base, class OffsetT>
	TFReverseIterator<Base, OffsetT> TFReverseIterator<Base, OffsetT>::operator++(int) noexcept
	{
		TFReverseIterator<Base, OffsetT> result = *this;
		++(*this);
		return *this;
	}
	
	template<class Base, class OffsetT>
	TFReverseIterator<Base, OffsetT> &TFReverseIterator<Base, OffsetT>::operator--() noexcept
	{
		++m_base;
		return *this;
	}
	
	template<class Base, class OffsetT>
	TFReverseIterator<Base, OffsetT> TFReverseIterator<Base, OffsetT>::operator--(int) noexcept
	{
		TFReverseIterator<Base, OffsetT> result = *this;
		--(*this);
		return *this;
	}
	
	template<class Base, class OffsetT>
	TFReverseIterator<Base, OffsetT> &TFReverseIterator<Base, OffsetT>::operator+=(OffsetT offset) noexcept
	{
		m_base -= offset;
		return *this;
	}
	
	template<class Base, class OffsetT>
	TFReverseIterator<Base, OffsetT> TFReverseIterator<Base, OffsetT>::operator+(OffsetT offset) const noexcept
	{
		TFReverseIterator<Base, OffsetT> result = *this;
		(*this) += offset;
		return *this;
	}
	
	template<class Base, class OffsetT>
	TFReverseIterator<Base, OffsetT> &TFReverseIterator<Base, OffsetT>::operator-=(OffsetT offset) noexcept
	{
		m_base += offset;
		return *this;
	}
	
	template<class Base, class OffsetT>
	TFReverseIterator<Base, OffsetT> TFReverseIterator<Base, OffsetT>::operator-(OffsetT offset) const noexcept
	{
		TFReverseIterator<Base, OffsetT> result = *this;
		(*this) -= offset;
		return *this;
	}
	
	template<class Base, class OffsetT>
	OffsetT TFReverseIterator<Base, OffsetT>::operator+(const TFReverseIterator &other) const noexcept
	{
		return m_base + other.m_base;
	}
	
	template<class Base, class OffsetT>
	OffsetT TFReverseIterator<Base, OffsetT>::operator-(const TFReverseIterator &other) const noexcept
	{
		return other.m_base - m_base;
	}
	
	template<class Base, class OffsetT>
	Bool TFReverseIterator<Base, OffsetT>::operator==(const TFReverseIterator &other) const noexcept
	{
		return m_base == other.m_base;
	}
	
	template<class Base, class OffsetT>
	Bool TFReverseIterator<Base, OffsetT>::operator!=(const TFReverseIterator &other) const noexcept
	{
		return m_base != other.m_base;
	}
	
	template<class Base, class OffsetT>
	std::strong_ordering TFReverseIterator<Base, OffsetT>::operator<=>(const TFReverseIterator &other) const noexcept
	{
		return other.m_base <=> m_base; // reversal
	}
	
	template<class Base, class OffsetT>
	auto &TFReverseIterator<Base, OffsetT>::operator*() noexcept
	{
		return *m_base;
	}
	
	template<class Base, class OffsetT>
	auto &TFReverseIterator<Base, OffsetT>::operator[](OffsetT offset) noexcept
	{
		return m_base[offset];
	}
	
	template<class Base, class OffsetT>
	auto *TFReverseIterator<Base, OffsetT>::operator->() noexcept
	{
		return m_base.operator->();
	}
	
	template<class Base, class OffsetTT>
	auto &TFReverseIterator<Base, OffsetTT>::operator*() const noexcept
	{
		return *m_base;
	}
	
	template<class Base, class OffsetT>
	auto &TFReverseIterator<Base, OffsetT>::operator[](OffsetT offset) const noexcept
	{
		return m_base[offset];
	}
	
	template<class Base, class OffsetT>
	auto *TFReverseIterator<Base, OffsetT>::operator->() const noexcept
	{
		return m_base.operator->();
	}
	
} // Whale
