//
// Created by admin on 2024/7/15.
//

#pragma once

#include "Whale/Core/Tool/HTypeDef.hpp"
#include "Whale/Core/Tool/FCString.hpp"
#include "Whale/Tool/Math/TFMath.hpp"
#include "TFArray.hpp"

namespace Whale
{
	
	///
	/// 字符串
	/// \tparam CharT
	template<class CharT>
	class WHALE_API TFString : public TFArray<CharT>
	{
	public:
		
		inline TFString();
		
		inline TFString(std::initializer_list<CharT> initializerList); // NOLINT(*-explicit-constructor)
		
		inline TFString(const CharT *first, const CharT *last);
		
		inline TFString(const CharT *str, SizeT length);
		
		inline TFString(const CharT *str); // NOLINT(*-explicit-constructor)
		
		inline TFString(const TFString &other);
		
		inline TFString(TFString &&other) noexcept;
		
		inline ~TFString() noexcept;
	
	public:
		
		inline TFString &operator=(TFString other) noexcept;
		
		Bool operator<(const TFString &other) const;
		
		Bool operator<=(const TFString &other) const;
		
		Bool operator>(const TFString &other) const;
		
		Bool operator>=(const TFString &other) const;
	
	public:
		
		[[nodiscard]]
		inline SizeT GetLengthNoNull() const noexcept
		{
			return this->GetLength() - 1;
		}
		
		inline const CharT *CStr() const noexcept
		{
			return TFArray<CharT>::GetPtr();
		}
		
	};
	
	using StringA = TFString<Char>;
	
	using StringW = TFString<WChar>;
	using StringT = TFString<TChar>;
	
	template<class CharT>
	TFString<CharT>::TFString()
		: TFArray<CharT>{}
	{
	
	}
	
	template<class CharT>
	TFString<CharT>::TFString(std::initializer_list<CharT> initializerList)
		: TFArray<CharT>(initializerList)
	{
	
	}
	
	template<class CharT>
	TFString<CharT>::TFString(const CharT *first, const CharT *last)
		: TFArray<CharT>(first, last)
	{
	
	}
	
	template<class CharT>
	TFString<CharT>::TFString(const CharT *str, SizeT length)
		: TFArray<CharT>{str, length}
	{
	
	}
	
	template<class CharT>
	TFString<CharT>::TFString(const CharT *str)
		: TFArray<CharT>{str, FCString::Length<CharT>(str)}
	{
	
	}
	
	template<class CharT>
	TFString<CharT>::TFString(const TFString &other)
		: TFArray<CharT>{other}
	{
	
	}
	
	template<class CharT>
	TFString<CharT>::TFString(TFString &&other) noexcept
		: TFArray<CharT>{other}
	{
	
	}
	
	template<class CharT>
	TFString<CharT>::~TFString() noexcept
	{
	
	}
	
	template<class CharT>
	TFString<CharT> &TFString<CharT>::operator=(TFString other) noexcept
	{
		TFArray<CharT>::Swap(other);
		return *this;
	}
	
	template<class CharT>
	Bool TFString<CharT>::operator<(const TFString &other) const
	{
		SizeT thisLength = GetLengthNoNull(), otherLength = other.GetLengthNoNull();
		SizeT minSize = TFMath<SizeT>::Min(thisLength, otherLength);
		for (SizeT index = 0; index < minSize; index++)
		{
			CharT thisChar = this->At(index), otherChar = other.At(index);
			if (thisChar < otherChar) return true;
			if (thisChar == otherChar) continue;
			return false;
		}
		return thisLength < otherLength;
	}
	
	template<class CharT>
	Bool TFString<CharT>::operator<=(const TFString &other) const
	{
		SizeT thisLength = GetLengthNoNull(), otherLength = other.GetLengthNoNull();
		SizeT minSize = TFMath<SizeT>::Min(thisLength, otherLength);
		for (SizeT index = 0; index < minSize; index++)
		{
			CharT thisChar = this->At(index), otherChar = other.At(index);
			if (thisChar <= otherChar) return true;
			if (thisChar == otherChar) continue;
			return false;
		}
		return thisLength <= otherLength;
	}
	
	template<class CharT>
	Bool TFString<CharT>::operator>(const TFString &other) const
	{
		SizeT thisLength = GetLengthNoNull(), otherLength = other.GetLengthNoNull();
		SizeT minSize = TFMath<SizeT>::Min(thisLength, otherLength);
		for (SizeT index = 0; index < minSize; index++)
		{
			CharT thisChar = this->At(index), otherChar = other.At(index);
			if (thisChar > otherChar) return true;
			if (thisChar == otherChar) continue;
			return false;
		}
		return thisLength > otherLength;
	}
	
	template<class CharT>
	Bool TFString<CharT>::operator>=(const TFString &other) const
	{
		SizeT thisLength = GetLengthNoNull(), otherLength = other.GetLengthNoNull();
		SizeT minSize = TFMath<SizeT>::Min(thisLength, otherLength);
		for (SizeT index = 0; index < minSize; index++)
		{
			CharT thisChar = this->At(index), otherChar = other.At(index);
			if (thisChar >= otherChar) return true;
			if (thisChar == otherChar) continue;
			return false;
		}
		return thisLength >= otherLength;
	}
	
} // Whale
