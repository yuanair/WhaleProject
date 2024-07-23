//
// Created by admin on 2024/7/15.
//

#pragma once

#include "Whale/Core/Utility.hpp"
#include "Whale/Core/CRT.hpp"
#include "Whale/Core/TFMath.hpp"
#include "InitList.hpp"

namespace Whale::Container
{
	
	///
	/// 非固定长度数组
	/// \tparam ElemT 元素类型
	template<class ElemT>
	class WHALE_API TFArray
	{
	public:
		
		TFArray();
		
		TFArray(std::initializer_list<ElemT> initializerList); // NOLINT(*-explicit-constructor)
		
		TFArray(const ElemT *first, const ElemT *last);
		
		TFArray(const ElemT *ptr, SizeT length);
		
		template<SizeT length>
		TFArray(const ElemT (&ptr)[length]) // NOLINT(*-explicit-constructor)
			: length(length), ptr(WHALE_NEW_CLIENT ElemT[length])
		{
			for (SizeT index = 0; index < length; index++)
			{
				this->ptr[index] = ptr[index];
			}
			
		}
		
		TFArray(const TFArray &other);
		
		TFArray(TFArray &&other) noexcept;
		
		virtual ~TFArray() noexcept;
	
	public:
		
		inline TFArray &operator=(TFArray other) noexcept;
		
		inline Bool operator==(const TFArray &other) const noexcept { return Equal(other); }
		
		inline Bool operator!=(const TFArray &other) const noexcept { return !Equal(other); }
		
		inline ElemT &operator[](SizeT index) noexcept { return At(index); }
		
		inline const ElemT &operator[](SizeT index) const noexcept { return At(index); }
	
	public:
		
		///
		/// 查找第一个元素
		ElemT *Find(const ElemT &elem, SizeT offset = 0) const noexcept;
		
		///
		/// 查找最后一个元素
		ElemT *RFind(const ElemT &elem, SizeT offset = 0) const noexcept;
		
		///
		/// 交换数据
		/// \param other
		void Swap(TFArray &other) noexcept;
		
		///
		/// 清空
		void Clear() noexcept;
		
		///
		/// 判断相等
		/// \param other
		/// \return
		Bool Equal(const TFArray &other) const noexcept;
		
		///
		/// 改变数组长度
		/// \param newLength 新长度
		virtual void Relength(SizeT newLength) noexcept;
		
		///
		/// 添加元素
		/// \param elem
		virtual ElemT &Append(const ElemT &elem) noexcept;
		
		///
		/// 添加元素
		/// \param array
		virtual ElemT &Append(const TFArray &array) noexcept;
		
		///
		/// 添加元素
		/// \param array
		virtual ElemT &Append(TFArray &&array) noexcept;
	
	public:
		
		ElemT &At(SizeT index) noexcept;
		
		const ElemT &At(SizeT index) const noexcept;
		
		ElemT *Begin() noexcept { return GetPtr(); }
		
		const ElemT *Begin() const noexcept { return GetPtr(); }
		
		ElemT *End() noexcept { return GetPtr() + GetLength(); }
		
		const ElemT *End() const noexcept { return GetPtr() + GetLength(); }
		
		ElemT *RBegin() noexcept { return GetPtr() + GetLength() - 1; }
		
		const ElemT *RBegin() const noexcept { return GetPtr() + GetLength() - 1; }
		
		ElemT *REnd() noexcept { return GetPtr() - 1; }
		
		const ElemT *REnd() const noexcept { return GetPtr() - 1; }
		
		/// for foreach
		ElemT *begin() noexcept { return Begin(); }
		
		/// for foreach
		const ElemT *begin() const noexcept { return Begin(); }
		
		/// for foreach
		ElemT *end() noexcept { return End(); }
		
		/// for foreach
		const ElemT *end() const noexcept { return End(); }
		
		/// for foreach
		ElemT *rbegin() noexcept { return RBegin(); }
		
		/// for foreach
		const ElemT *rbegin() const noexcept { return RBegin(); }
		
		/// for foreach
		ElemT *rend() noexcept { return REnd(); }
		
		/// for foreach
		const ElemT *rend() const noexcept { return REnd(); }
	
	public:
		
		///
		/// \return 是否为空
		[[nodiscard]]
		SizeT IsEmpty() const noexcept { return GetLength() == 0; }
		
		///
		/// \return 数组长度
		[[nodiscard]]
		virtual SizeT GetLength() const noexcept { return this->length; }
		
		///
		/// \return 数据指针
		const ElemT *GetPtr() const noexcept { return this->ptr; }
		
		///
		/// \return 数据指针
		ElemT *GetPtr() noexcept { return this->ptr; }
	
	protected:
		
		ElemT &ProtectedAt(SizeT index) noexcept;
		
		const ElemT &ProtectedAt(SizeT index) const noexcept;
	
	private:
		
		void PrivateReset(ElemT *newPtr) noexcept;
	
	private:
		
		SizeT length;
		
		ElemT *ptr;
		
	};
	
	template<class ElemT>
	ElemT *TFArray<ElemT>::Find(const ElemT &elem, SizeT offset) const noexcept
	{
		if (offset >= GetLength()) return End();
		ElemT *iter = Begin() + offset;
		for (; iter != End(); iter++)
		{
			if (elem == *iter) return iter;
		}
		return iter;
	}
	
	template<class ElemT>
	ElemT *TFArray<ElemT>::RFind(const ElemT &elem, SizeT offset) const noexcept
	{
		if (offset >= GetLength()) return REnd();
		ElemT *iter = RBegin() + offset;
		for (; iter != REnd(); iter--)
		{
			if (elem == *iter) return iter;
		}
		return iter;
	}
	
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
		PrivateReset(nullptr);
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
	void TFArray<ElemT>::Clear() noexcept
	{
		TFArray<ElemT>().Swap(*this);
	}
	
	template<class ElemT>
	Bool TFArray<ElemT>::Equal(const TFArray &other) const noexcept
	{
		if (&other == this) return true;
		if (this->length != other.length) return false;
		for (SizeT index = 0; index < this->length; index++)
		{
			if (ProtectedAt(index) != other.ProtectedAt(index)) return false;
		}
		return true;
	}
	
	template<class ElemT>
	void TFArray<ElemT>::Relength(SizeT newLength) noexcept
	{
		auto newPtr = WHALE_NEW_CLIENT ElemT[newLength];
		auto minLength = TFMath<SizeT>::Min(this->length, newLength);
		for (SizeT index = 0; index < minLength; index++)
		{
			newPtr[index] = Whale::Move(this->ptr[index]);
		}
		PrivateReset(newPtr);
		this->length = newLength;
	}
	
	template<class ElemT>
	ElemT &TFArray<ElemT>::Append(const ElemT &elem) noexcept
	{
		SizeT oldLength = GetLength();
		Relength(oldLength + 1);
		return At(oldLength) = elem;
	}
	
	template<class ElemT>
	ElemT &TFArray<ElemT>::Append(const TFArray &array) noexcept
	{
		SizeT oldLength = GetLength();
		Relength(oldLength + array.GetLength());
		for (SizeT index = 0; index < array.GetLength(); index++)
		{
			At(oldLength + index) = array.At(index);
		}
		return At(GetLength() - 1);
	}
	
	template<class ElemT>
	ElemT &TFArray<ElemT>::Append(TFArray &&array) noexcept
	{
		SizeT oldLength = GetLength();
		Relength(oldLength + array.GetLength());
		for (SizeT index = 0; index < array.GetLength(); index++)
		{
			At(oldLength + index) = Whale::Move(array.At(index));
		}
		array.Clear();
		return At(GetLength() - 1);
	}
	
	template<class ElemT>
	ElemT &TFArray<ElemT>::At(SizeT index) noexcept
	{
		WHALE_ASSERT(index < GetLength());
		return this->ptr[index];
	}
	
	template<class ElemT>
	const ElemT &TFArray<ElemT>::At(SizeT index) const noexcept
	{
		WHALE_ASSERT(index < GetLength());
		return this->ptr[index];
	}
	
	template<class ElemT>
	ElemT &TFArray<ElemT>::ProtectedAt(SizeT index) noexcept
	{
		WHALE_ASSERT(index < this->length);
		return this->ptr[index];
	}
	
	template<class ElemT>
	const ElemT &TFArray<ElemT>::ProtectedAt(SizeT index) const noexcept
	{
		WHALE_ASSERT(index < this->length);
		return this->ptr[index];
	}
	
	template<class ElemT>
	void TFArray<ElemT>::PrivateReset(ElemT *newPtr) noexcept
	{
		if (this->ptr != nullptr) delete[] this->ptr;
		this->ptr = newPtr;
	}
	
} // Whale
