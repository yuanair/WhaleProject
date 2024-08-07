//
// Created by admin on 2024/8/5.
//

#pragma once

#include "../Utility.hpp"
#include "TIIterator.hpp"

namespace Whale::Container
{
	
	template<class ElemT, class OffsetT>
	class WHALE_API TIConstPointerIterator : public TIIterator<ElemT>
	{
	public:
		
		using OffsetType = OffsetT;
		
		using Base = TIIterator<ElemT>;
	
	public:
		
		explicit TIConstPointerIterator(const ElemT *ptr) noexcept: ptr(ptr) {}
		
		~TIConstPointerIterator() noexcept = default;
	
	public:
		
		TIConstPointerIterator &operator++() noexcept;
		
		TIConstPointerIterator operator++(int) noexcept;
		
		TIConstPointerIterator &operator--() noexcept;
		
		TIConstPointerIterator operator--(int) noexcept;
		
		TIConstPointerIterator &operator+=(OffsetT offset) noexcept;
		
		TIConstPointerIterator operator+(OffsetT offset) const noexcept;
		
		TIConstPointerIterator &operator-=(OffsetT offset) noexcept;
		
		TIConstPointerIterator operator-(OffsetT offset) const noexcept;
		
		OffsetT operator+(const TIConstPointerIterator &other) const noexcept;
		
		OffsetT operator-(const TIConstPointerIterator &other) const noexcept;
		
		Bool operator==(const TIConstPointerIterator &other) const noexcept;
		
		Bool operator!=(const TIConstPointerIterator &other) const noexcept;
		
		std::strong_ordering operator<=>(const TIConstPointerIterator &other) const noexcept;
		
		const ElemT &operator*() const noexcept;
		
		const ElemT &operator[](OffsetT offset) const noexcept;
		
		const ElemT *operator->() const noexcept;
	
	public:
		
		[[nodiscard]] const ElemT *GetPtr() const { return ptr; }
	
	private:
		
		const ElemT *ptr;
		
	};
	
	template<class ElemT, class OffsetT>
	class WHALE_API TIPointerIterator : public TIConstPointerIterator<ElemT, OffsetT>
	{
	public:
		
		using Base = TIConstPointerIterator<ElemT, OffsetT>;
	
	public:
		
		explicit TIPointerIterator(ElemT *ptr) noexcept: TIConstPointerIterator<ElemT, OffsetT>(ptr) {}
	
	public:
		
		TIPointerIterator &operator++() noexcept;
		
		TIPointerIterator operator++(int) noexcept;
		
		TIPointerIterator &operator--() noexcept;
		
		TIPointerIterator operator--(int) noexcept;
		
		TIPointerIterator &operator+=(OffsetT offset) noexcept;
		
		TIPointerIterator operator+(OffsetT offset) const noexcept;
		
		TIPointerIterator &operator-=(OffsetT offset) noexcept;
		
		TIPointerIterator operator-(OffsetT offset) const noexcept;
		
		OffsetT operator+(const TIPointerIterator &other) const noexcept;
		
		OffsetT operator-(const TIPointerIterator &other) const noexcept;
		
		ElemT &operator*() noexcept;
		
		ElemT &operator[](OffsetT offset) noexcept;
		
		ElemT *operator->() noexcept;
		
		const ElemT &operator*() const noexcept;
		
		const ElemT &operator[](OffsetT offset) const noexcept;
		
		const ElemT *operator->() const noexcept;
		
	};
	
	
	template<class ElemT, class OffsetT>
	TIConstPointerIterator<ElemT, OffsetT> &TIConstPointerIterator<ElemT, OffsetT>::operator++() noexcept
	{
		++ptr;
		return *this;
	}
	
	template<class ElemT, class OffsetT>
	TIConstPointerIterator<ElemT, OffsetT> TIConstPointerIterator<ElemT, OffsetT>::operator++(int) noexcept
	{
		TIConstPointerIterator iterator = *this;
		++(*this);
		return iterator;
	}
	
	template<class ElemT, class OffsetT>
	TIConstPointerIterator<ElemT, OffsetT> &TIConstPointerIterator<ElemT, OffsetT>::operator--() noexcept
	{
		--ptr;
		return *this;
	}
	
	template<class ElemT, class OffsetT>
	TIConstPointerIterator<ElemT, OffsetT> TIConstPointerIterator<ElemT, OffsetT>::operator--(int) noexcept
	{
		TIConstPointerIterator iterator = *this;
		--(*this);
		return iterator;
	}
	
	
	template<class ElemT, class OffsetT>
	TIConstPointerIterator<ElemT, OffsetT> &TIConstPointerIterator<ElemT, OffsetT>::operator+=(OffsetT offset) noexcept
	{
		ptr += offset;
		return *this;
	}
	
	template<class ElemT, class OffsetT>
	TIConstPointerIterator<ElemT, OffsetT>
	TIConstPointerIterator<ElemT, OffsetT>::operator+(OffsetT offset) const noexcept
	{
		return TIConstPointerIterator(ptr + offset);
	}
	
	template<class ElemT, class OffsetT>
	TIConstPointerIterator<ElemT, OffsetT> &TIConstPointerIterator<ElemT, OffsetT>::operator-=(OffsetT offset) noexcept
	{
		ptr -= offset;
		return *this;
	}
	
	template<class ElemT, class OffsetT>
	TIConstPointerIterator<ElemT, OffsetT>
	TIConstPointerIterator<ElemT, OffsetT>::operator-(OffsetT offset) const noexcept
	{
		return TIConstPointerIterator(ptr - offset);
	}
	
	template<class ElemT, class OffsetT>
	OffsetT TIConstPointerIterator<ElemT, OffsetT>::operator+(const TIConstPointerIterator &other) const noexcept
	{
		return ptr + other.ptr;
	}
	
	template<class ElemT, class OffsetT>
	OffsetT TIConstPointerIterator<ElemT, OffsetT>::operator-(const TIConstPointerIterator &other) const noexcept
	{
		return ptr - other.ptr;
	}
	
	template<class ElemT, class OffsetT>
	Bool TIConstPointerIterator<ElemT, OffsetT>::operator==(const TIConstPointerIterator &other) const noexcept
	{
		return ptr == other.ptr;
	}
	
	template<class ElemT, class OffsetT>
	Bool TIConstPointerIterator<ElemT, OffsetT>::operator!=(const TIConstPointerIterator &other) const noexcept
	{
		return ptr != other.ptr;
	}
	
	template<class ElemT, class OffsetT>
	std::strong_ordering
	TIConstPointerIterator<ElemT, OffsetT>::operator<=>(const TIConstPointerIterator &other) const noexcept
	{
		return ptr <=> other.ptr;
	}
	
	template<class ElemT, class OffsetT>
	const ElemT &TIConstPointerIterator<ElemT, OffsetT>::operator*() const noexcept
	{
		return *ptr;
	}
	
	template<class ElemT, class OffsetT>
	const ElemT &TIConstPointerIterator<ElemT, OffsetT>::operator[](OffsetT offset) const noexcept
	{
		return ptr[offset];
	}
	
	template<class ElemT, class OffsetT>
	const ElemT *TIConstPointerIterator<ElemT, OffsetT>::operator->() const noexcept
	{
		return ptr;
	}
	
	
	template<class ElemT, class OffsetT>
	TIPointerIterator<ElemT, OffsetT> &TIPointerIterator<ElemT, OffsetT>::operator++() noexcept
	{
		Base::operator++();
		return *this;
	}
	
	template<class ElemT, class OffsetT>
	TIPointerIterator<ElemT, OffsetT> TIPointerIterator<ElemT, OffsetT>::operator++(int) noexcept
	{
		TIPointerIterator result = *this;
		Base::operator++();
		return result;
	}
	
	template<class ElemT, class OffsetT>
	TIPointerIterator<ElemT, OffsetT> &TIPointerIterator<ElemT, OffsetT>::operator--() noexcept
	{
		Base::operator--();
		return *this;
	}
	
	template<class ElemT, class OffsetT>
	TIPointerIterator<ElemT, OffsetT> TIPointerIterator<ElemT, OffsetT>::operator--(int) noexcept
	{
		TIPointerIterator result = *this;
		Base::operator--();
		return result;
	}
	
	template<class ElemT, class OffsetT>
	TIPointerIterator<ElemT, OffsetT> &TIPointerIterator<ElemT, OffsetT>::operator+=(OffsetT offset) noexcept
	{
		Base::operator+=(offset);
		return *this;
	}
	
	template<class ElemT, class OffsetT>
	TIPointerIterator<ElemT, OffsetT> TIPointerIterator<ElemT, OffsetT>::operator+(OffsetT offset) const noexcept
	{
		TIPointerIterator result = *this;
		Base::operator+=(offset);
		return result;
	}
	
	template<class ElemT, class OffsetT>
	TIPointerIterator<ElemT, OffsetT> &TIPointerIterator<ElemT, OffsetT>::operator-=(OffsetT offset) noexcept
	{
		Base::operator-=(offset);
		return *this;
	}
	
	template<class ElemT, class OffsetT>
	TIPointerIterator<ElemT, OffsetT> TIPointerIterator<ElemT, OffsetT>::operator-(OffsetT offset) const noexcept
	{
		TIPointerIterator result = *this;
		Base::operator-=(offset);
		return result;
	}
	
	template<class ElemT, class OffsetT>
	OffsetT TIPointerIterator<ElemT, OffsetT>::operator+(const TIPointerIterator &other) const noexcept
	{
		return Base::operator+(other);
	}
	
	template<class ElemT, class OffsetT>
	OffsetT TIPointerIterator<ElemT, OffsetT>::operator-(const TIPointerIterator &other) const noexcept
	{
		return Base::operator-(other);
	}
	
	template<class ElemT, class OffsetT>
	ElemT &TIPointerIterator<ElemT, OffsetT>::operator*() noexcept
	{
		return const_cast<ElemT &>(Base::operator*());
	}
	
	template<class ElemT, class OffsetT>
	ElemT &TIPointerIterator<ElemT, OffsetT>::operator[](OffsetT offset) noexcept
	{
		return const_cast<ElemT &>(Base::operator[](offset));
	}
	
	template<class ElemT, class OffsetT>
	ElemT *TIPointerIterator<ElemT, OffsetT>::operator->() noexcept
	{
		return const_cast<ElemT *>(Base::operator->());
	}
	
	template<class ElemT, class OffsetT>
	const ElemT &TIPointerIterator<ElemT, OffsetT>::operator*() const noexcept
	{
		return Base::operator*();
	}
	
	template<class ElemT, class OffsetT>
	const ElemT &TIPointerIterator<ElemT, OffsetT>::operator[](OffsetT offset) const noexcept
	{
		return Base::operator[](offset);
	}
	
	template<class ElemT, class OffsetT>
	const ElemT *TIPointerIterator<ElemT, OffsetT>::operator->() const noexcept
	{
		return Base::operator->();
	}
	
} // Whale
