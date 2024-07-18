//
// Created by admin on 2024/7/15.
//

#pragma once

#include "Whale/Core/Tool/HTypeDef.hpp"
#include "Whale/Core/Tool/HCRT.hpp"
#include <initializer_list>

namespace Whale
{
	
	///
	/// 非固定长度数组
	/// \tparam ElemT 元素类型
	template<class ElemT>
	class WHALE_API TFArray
	{
	public:
		
		inline TFArray();
		
		inline TFArray(std::initializer_list<ElemT> initializerList); // NOLINT(*-explicit-constructor)
		
		inline TFArray(const ElemT *first, const ElemT *last);
		
		inline TFArray(const ElemT *ptr, SizeT length);
		
		template<SizeT length>
		inline TFArray(const ElemT (&ptr)[length]) // NOLINT(*-explicit-constructor)
			: length(length), ptr(WHALE_NEW_CLIENT ElemT[length])
		{
			for (SizeT index = 0; index < length; index++)
			{
				this->ptr[index] = ptr[index];
			}
			
		}
		
		inline TFArray(const TFArray &other);
		
		inline TFArray(TFArray &&other) noexcept;
		
		inline ~TFArray() noexcept;
	
	public:
		
		inline TFArray &operator=(TFArray other) noexcept;
		
		inline ElemT &operator[](SizeT index) noexcept { return At(index); }
		
		inline const ElemT &operator[](SizeT index) const noexcept { return At(index); }
	
	public:
		
		inline void Swap(TFArray &other) noexcept;
		
		inline Bool Equal(const TFArray &other) const noexcept;
		
		inline ElemT &At(SizeT index) noexcept;
		
		inline const ElemT &At(SizeT index) const noexcept;
	
	public:
		
		inline ElemT *Begin() const noexcept
		{
			return this->ptr;
		}
		
		inline ElemT *End() const noexcept
		{
			return this->ptr + this->length;
		}
		
		/// for foreach
		constexpr const ElemT *begin() const noexcept { return Begin(); }
		
		/// for foreach
		constexpr const ElemT *end() const noexcept { return End(); }
		
		[[nodiscard]]
		inline SizeT GetLength() const noexcept { return this->length; }
		
		inline const ElemT *GetPtr() const noexcept { return this->ptr; }
		
		inline ElemT *GetPtr() noexcept { return this->ptr; }
	
	private:
		
		SizeT length;
		
		ElemT *ptr;
		
	};
	
	template<class ElemT>
	TFArray<ElemT>::TFArray(std::initializer_list<ElemT> initializerList)
		: TFArray(initializerList.begin(), initializerList.end())
	{
	
	}
	
	template<class ElemT>
	TFArray<ElemT>::TFArray(const ElemT *first, const ElemT *last)
		: length((SizeT) (last - first)), ptr(nullptr)
	{
		this->ptr = WHALE_NEW_CLIENT ElemT[length];
		ElemT *target = this->ptr;
		while (first != last)
		{
			*(target++) = *(first++);
		}
	}
	
	template<class ElemT>
	TFArray<ElemT>::TFArray(const ElemT *ptr, SizeT length)
		: length(length), ptr(WHALE_NEW_CLIENT ElemT[length])
	{
		if (ptr == nullptr) return;
		for (SizeT index = 0; index < length; index++)
		{
			this->ptr[index] = ptr[index];
		}
	}
	
	template<class ElemT>
	TFArray<ElemT>::TFArray()
		: length(0), ptr(WHALE_NEW_CLIENT ElemT[0])
	{
	
	}
	
	template<class ElemT>
	TFArray<ElemT>::TFArray(const TFArray &other)
		: length(other.length), ptr(WHALE_NEW_CLIENT ElemT[other.length])
	{
		for (SizeT index = 0; index < this->length; index++)
		{
			this->ptr[index] = other.ptr[index];
		}
	}
	
	template<class ElemT>
	TFArray<ElemT>::TFArray(TFArray &&other) noexcept
		: TFArray()
	{
		Swap(other);
	}
	
	template<class ElemT>
	TFArray<ElemT>::~TFArray() noexcept
	{
		if (this->ptr == nullptr) return;
		delete[] this->ptr;
		this->ptr = nullptr;
		this->length = 0;
	}
	
	template<class ElemT>
	TFArray<ElemT> &TFArray<ElemT>::operator=(TFArray other) noexcept
	{
		Swap(other);
		return *this;
	}
	
	template<class ElemT>
	void TFArray<ElemT>::Swap(TFArray &other) noexcept
	{
		Whale::Swap(this->ptr, other.ptr);
		Whale::Swap(this->length, other.length);
	}
	
	template<class ElemT>
	Bool TFArray<ElemT>::Equal(const TFArray &other) const noexcept
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
	ElemT &TFArray<ElemT>::At(SizeT index) noexcept
	{
		WHALE_ASSERT(index < this->length);
		return this->ptr[index];
	}
	
	template<class ElemT>
	const ElemT &TFArray<ElemT>::At(SizeT index) const noexcept
	{
		WHALE_ASSERT(index < this->length);
		return this->ptr[index];
	}
	
} // Whale
