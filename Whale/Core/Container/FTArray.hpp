//
// Created by admin on 2024/7/15.
//

#pragma once

#include "Whale/Core/Tool/FTypeDef.hpp"
#include "Whale/Core/Tool/FTInitializerList.hpp"
#include "Whale/Core/Tool/FCRT.hpp"

namespace Whale
{
	
	///
	/// 非固定长度数组
	/// \tparam ElemT 元素类型
	template<class ElemT>
	class WHALE_API FTArray
	{
	public:
		
		inline FTArray();
		
		inline FTArray(const FTInitializerList<ElemT> &initializerList); // NOLINT(*-explicit-constructor)
		
		inline FTArray(const ElemT *first, const ElemT *last);
		
		inline FTArray(const ElemT *ptr, SizeT length);
		
		template<SizeT length>
		inline FTArray(const ElemT (&ptr)[length]) // NOLINT(*-explicit-constructor)
			: length(length), ptr(WHALE_DBG_NEW ElemT[length])
		{
			for (SizeT index = 0; index < length; index++)
			{
				this->ptr[index] = ptr[index];
			}
			
		}
		
		inline FTArray(const FTArray &other);
		
		inline FTArray(FTArray &&other) noexcept;
		
		inline ~FTArray() noexcept;
	
	public:
		
		inline FTArray &operator=(FTArray other) noexcept;
		
		inline ElemT &operator[](SizeT index) noexcept { return At(index); }
		
		inline const ElemT &operator[](SizeT index) const noexcept { return At(index); }
	
	public:
		
		inline void Swap(FTArray &other) noexcept;
		
		inline Bool Equal(const FTArray &other) const noexcept;
		
		inline ElemT &At(SizeT index) noexcept;
		
		inline const ElemT &At(SizeT index) const noexcept;
	
	public:
		
		inline ElemT *Begin() const noexcept
		{
			return ptr;
		}
		
		inline ElemT *End() const noexcept
		{
			return ptr + length;
		}
		
		/// for foreach
		constexpr const ElemT *begin() const noexcept { return Begin(); }
		
		/// for foreach
		constexpr const ElemT *end() const noexcept { return End(); }
		
		[[nodiscard]]
		inline SizeT GetLength() const noexcept
		{
			return length;
		}
		
		inline ElemT *GetPtr() const noexcept
		{
			return ptr;
		}
	
	private:
		
		SizeT length;
		
		ElemT *ptr;
		
	};
	
	template<class ElemT>
	FTArray<ElemT>::FTArray(const FTInitializerList<ElemT> &initializerList)
		: FTArray(initializerList.begin(), initializerList.end())
	{
	
	}
	
	template<class ElemT>
	FTArray<ElemT>::FTArray(const ElemT *first, const ElemT *last)
		: length((SizeT) (last - first)), ptr(nullptr)
	{
		this->ptr = WHALE_DBG_NEW ElemT[length];
		ElemT *target = this->ptr;
		while (first != last)
		{
			*(target++) = *(first++);
		}
	}
	
	template<class ElemT>
	FTArray<ElemT>::FTArray(const ElemT *ptr, SizeT length)
		: length(length), ptr(WHALE_DBG_NEW ElemT[length])
	{
		for (SizeT index = 0; index < length; index++)
		{
			this->ptr[index] = ptr[index];
		}
	}
	
	template<class ElemT>
	FTArray<ElemT>::FTArray()
		: length(0), ptr(WHALE_DBG_NEW ElemT[0])
	{
	
	}
	
	template<class ElemT>
	FTArray<ElemT>::FTArray(const FTArray &other)
		: length(other.length), ptr(WHALE_DBG_NEW ElemT[other.length])
	{
		for (SizeT index = 0; index < this->length; index++)
		{
			this->ptr[index] = other.ptr[index];
		}
	}
	
	template<class ElemT>
	FTArray<ElemT>::FTArray(FTArray &&other) noexcept
		: FTArray()
	{
		Swap(other);
	}
	
	template<class ElemT>
	FTArray<ElemT>::~FTArray() noexcept
	{
		if (this->ptr == nullptr) return;
		delete[] this->ptr;
		this->ptr = nullptr;
		this->length = 0;
	}
	
	template<class ElemT>
	FTArray<ElemT> &FTArray<ElemT>::operator=(FTArray other) noexcept
	{
		Swap(other);
		return *this;
	}
	
	template<class ElemT>
	void FTArray<ElemT>::Swap(FTArray &other) noexcept
	{
		Whale::Swap(this->ptr, other.ptr);
		Whale::Swap(this->length, other.length);
	}
	
	template<class ElemT>
	Bool FTArray<ElemT>::Equal(const FTArray &other) const noexcept
	{
		if (&other == this) return true;
		if (GetLength() != other.GetLength()) return false;
		for (SizeT index = 0; index < GetLength(); index++)
		{
			if (At(index) != other.At(index)) return false;
		}
		return true;
	}
	
	template<class ElemT>
	ElemT &FTArray<ElemT>::At(SizeT index) noexcept
	{
		WHALE_ASSERT(index < this->length);
		return this->ptr[index];
	}
	
	template<class ElemT>
	const ElemT &FTArray<ElemT>::At(SizeT index) const noexcept
	{
		WHALE_ASSERT(index < this->length);
		return this->ptr[index];
	}
	
} // Whale
