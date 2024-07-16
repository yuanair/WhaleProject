//
// Created by admin on 2024/7/15.
//

#pragma once

#include "Whale/Core/Object/WObject.hpp"
#include "Whale/Core/Tool/FCString.hpp"
#include "FTArray.hpp"

namespace Whale
{
	
	///
	/// 字符串
	/// \tparam CharT
	template<class CharT>
	class WHALE_API FTString : public FTArray<CharT>
	{
	public:
		
		inline FTString();
		
		inline FTString(const FTInitializerList<CharT> &initializerList); // NOLINT(*-explicit-constructor)
		
		inline FTString(const CharT *first, const CharT *last);
		
		inline FTString(const CharT *str, SizeT length);
		
		inline FTString(const CharT *str); // NOLINT(*-explicit-constructor)
		
		inline FTString(const FTString &other);
		
		inline FTString(FTString &&other) noexcept;
		
		inline ~FTString() noexcept;
	
	public:
		
		inline FTString &operator=(FTString other) noexcept;
	
	public:
		
		[[nodiscard]]
		inline SizeT GetLengthNoNull() const noexcept
		{
			return this->array.GetLength() - 1;
		}
		
		inline CharT *CStr() const noexcept
		{
			return FTArray<CharT>::GetPtr();
		}
		
	};
	
	using FTStringA = FTString<Char>;
	using FTStringW = FTString<WChar>;
	using FTStringT = FTString<TChar>;
	
	template<class CharT>
	FTString<CharT>::FTString()
		: FTArray<CharT>{}
	{
	
	}
	
	template<class CharT>
	FTString<CharT>::FTString(const FTInitializerList<CharT> &initializerList)
		: FTArray<CharT>(initializerList)
	{
	
	}
	
	template<class CharT>
	FTString<CharT>::FTString(const CharT *first, const CharT *last)
		: FTArray<CharT>(first, last)
	{
	
	}
	
	template<class CharT>
	FTString<CharT>::FTString(const CharT *str, SizeT length)
		: FTArray<CharT>{str, length}
	{
	
	}
	
	template<class CharT>
	FTString<CharT>::FTString(const CharT *str)
		: FTArray<CharT>{str, FCString<CharT>::Length(str)}
	{
	
	}
	
	template<class CharT>
	FTString<CharT>::FTString(const FTString &other)
		: FTArray<CharT>{other}
	{
	
	}
	
	template<class CharT>
	FTString<CharT>::FTString(FTString &&other) noexcept
		: FTArray<CharT>{other}
	{
	
	}
	
	template<class CharT>
	FTString<CharT>::~FTString() noexcept
	{
	
	}
	
	template<class CharT>
	FTString<CharT> &FTString<CharT>::operator=(FTString other) noexcept
	{
		FTArray<CharT>::Swap(other);
		return *this;
	}
	
} // Whale
