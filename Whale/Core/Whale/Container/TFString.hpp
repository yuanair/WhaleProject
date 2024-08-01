//
// Created by admin on 2024/7/15.
//

#pragma once

#include "../TypeDef.hpp"
#include "../FCString.hpp"
#include "../TFMath.hpp"
#include "TFArray.hpp"

namespace Whale::Container
{
	
	///
	/// 字符串
	/// \tparam ElemT
	template<class ElemT>
	class WHALE_API TFString final : public TFArray<ElemT>
	{
	public:
		
		inline TFString();
		
		inline TFString(std::initializer_list<ElemT> initializerList); // NOLINT(*-explicit-constructor)
		
		inline TFString(const ElemT *first, const ElemT *last);
		
		inline TFString(const ElemT *str, SizeT length);
		
		inline TFString(const ElemT *str); // NOLINT(*-explicit-constructor)
		
		inline TFString(const TFString &other);
		
		inline TFString(TFString &&other) noexcept;
		
		inline ~TFString() noexcept override;
	
	public:
		
		inline TFString &operator=(TFString other) noexcept;
		
		inline TFString &operator+=(TFString other) noexcept;
		
		inline TFString operator+(TFString other) const noexcept;
		
		inline Bool operator==(const TFString &other) const noexcept { return TFArray<ElemT>::Equal(other); }
		
		inline Bool operator!=(const TFString &other) const noexcept { return !TFArray<ElemT>::Equal(other); }
		
		Bool operator<(const TFString &other) const;
		
		Bool operator<=(const TFString &other) const;
		
		Bool operator>(const TFString &other) const;
		
		Bool operator>=(const TFString &other) const;
	
	public:
		
		void Relength(SizeT newLength) noexcept override
		{
			TFArray<ElemT>::Relength(newLength + 1);
		}
		
		ElemT &Append(ElemT elem) noexcept override
		{
			SizeT oldLength = GetLength();
			Relength(oldLength + 1);
			ElemT &result                  = this->At(oldLength) = elem;
			this->ProtectedAt(GetLength()) = 0;
			return result;
		}
		
		ElemT &Append(TFArray<ElemT> array) noexcept override
		{
			SizeT oldLength = GetLength();
			Relength(oldLength + array.GetLength());
			for (SizeT index   = 0; index < array.GetLength(); index++)
			{
				this->At(oldLength + index) = Whale::Move(array.At(index));
			}
			ElemT      &result = this->At(GetLength() - 1);
			this->ProtectedAt(GetLength()) = 0;
			return result;
		}
		
		ElemT &Append(TFString str) noexcept
		{
			SizeT oldLength = GetLength();
			Relength(oldLength + str.GetLength());
			for (SizeT index   = 0; index < str.GetLength(); index++)
			{
				this->At(oldLength + index) = Whale::Move(str.At(index));
			}
			ElemT      &result = this->At(GetLength() - 1);
			this->ProtectedAt(GetLength()) = 0;
			return result;
		}
	
	public:
		
		[[nodiscard]]
		inline SizeT GetLength() const noexcept override
		{
			return TFMath<SizeT>::Max(TFArray<ElemT>::GetLength(), 1) - 1;
		}
		
		inline const ElemT *CStr() const noexcept
		{
			return TFArray<ElemT>::GetPtr();
		}
		
	};
	
	template<class ElemT>
	inline TFString<ElemT> operator+(const ElemT *left, const TFString<ElemT> &right) noexcept
	{
		TFString<ElemT> result{left};
		result.Append(right);
		return result;
	}
	
	template<class ElemT>
	inline TFString<ElemT> operator+(const TFString<ElemT> &left, const TFString<ElemT> &right) noexcept
	{
		TFString<ElemT> result{left};
		result.Append(right);
		return result;
	}
	
	using StringA = TFString<CharA>;
	using StringW = TFString<CharW>;
	using StringT = TFString<CharT>;
	
	template<class ElemT>
	TFString<ElemT>::TFString()
		: TFArray<ElemT>{}
	{
	
	}
	
	template<class ElemT>
	TFString<ElemT>::TFString(std::initializer_list<ElemT> initializerList)
		: TFArray<ElemT>(initializerList)
	{
	
	}
	
	template<class ElemT>
	TFString<ElemT>::TFString(const ElemT *first, const ElemT *last)
		: TFArray<ElemT>(first, last)
	{
	
	}
	
	template<class ElemT>
	TFString<ElemT>::TFString(const ElemT *str, SizeT length)
		: TFArray<ElemT>{str, length}
	{
	
	}
	
	template<class ElemT>
	TFString<ElemT>::TFString(const ElemT *str)
		: TFArray<ElemT>{str, FCString::Length<ElemT>(str)}
	{
	
	}
	
	template<class ElemT>
	TFString<ElemT>::TFString(const TFString &other)
		: TFArray<ElemT>{other}
	{
	
	}
	
	template<class ElemT>
	TFString<ElemT>::TFString(TFString &&other) noexcept
		: TFArray<ElemT>{other}
	{
	
	}
	
	template<class ElemT>
	TFString<ElemT>::~TFString() noexcept
	{
	
	}
	
	template<class ElemT>
	TFString<ElemT> &TFString<ElemT>::operator=(TFString other) noexcept
	{
		TFArray<ElemT>::Swap(other);
		return *this;
	}
	
	template<class ElemT>
	TFString<ElemT> &TFString<ElemT>::operator+=(TFString other) noexcept
	{
		Append(Whale::Move(other));
		return *this;
	}
	
	template<class ElemT>
	TFString<ElemT> TFString<ElemT>::operator+(TFString other) const noexcept
	{
		TFString result{*this};
		result.Append(Whale::Move(other));
		return result;
	}
	
	template<class ElemT>
	Bool TFString<ElemT>::operator<(const TFString &other) const
	{
		SizeT      thisLength = GetLength(), otherLength = other.GetLength();
		SizeT      minSize    = TFMath<SizeT>::Min(thisLength, otherLength);
		for (SizeT index      = 0; index < minSize; index++)
		{
			ElemT thisChar = this->At(index), otherChar = other.At(index);
			if (thisChar < otherChar) return true;
			if (thisChar == otherChar) continue;
			return false;
		}
		return thisLength < otherLength;
	}
	
	template<class ElemT>
	Bool TFString<ElemT>::operator<=(const TFString &other) const
	{
		SizeT      thisLength = GetLength(), otherLength = other.GetLength();
		SizeT      minSize    = TFMath<SizeT>::Min(thisLength, otherLength);
		for (SizeT index      = 0; index < minSize; index++)
		{
			ElemT thisChar = this->At(index), otherChar = other.At(index);
			if (thisChar <= otherChar) return true;
			if (thisChar == otherChar) continue;
			return false;
		}
		return thisLength <= otherLength;
	}
	
	template<class ElemT>
	Bool TFString<ElemT>::operator>(const TFString &other) const
	{
		SizeT      thisLength = GetLength(), otherLength = other.GetLength();
		SizeT      minSize    = TFMath<SizeT>::Min(thisLength, otherLength);
		for (SizeT index      = 0; index < minSize; index++)
		{
			ElemT thisChar = this->At(index), otherChar = other.At(index);
			if (thisChar > otherChar) return true;
			if (thisChar == otherChar) continue;
			return false;
		}
		return thisLength > otherLength;
	}
	
	template<class ElemT>
	Bool TFString<ElemT>::operator>=(const TFString &other) const
	{
		SizeT      thisLength = GetLength(), otherLength = other.GetLength();
		SizeT      minSize    = TFMath<SizeT>::Min(thisLength, otherLength);
		for (SizeT index      = 0; index < minSize; index++)
		{
			ElemT thisChar = this->At(index), otherChar = other.At(index);
			if (thisChar >= otherChar) return true;
			if (thisChar == otherChar) continue;
			return false;
		}
		return thisLength >= otherLength;
	}
	
}

namespace Whale
{
	using Container::StringA;
	using Container::StringW;
	using Container::StringT;
	
	
	template<class Arg>
	StringA ToStringA(Arg &&arg) noexcept
	{
		StringA result;
		ToString(result, Whale::Forward<Arg>(arg));
		return result;
	}
	
	template<class Arg>
	StringW ToStringW(Arg &&arg) noexcept
	{
		StringW result;
		ToString(result, Whale::Forward<Arg>(arg));
		return result;
	}
	
	
	template<class Arg>
	void ToString(StringA &target, Arg arg) noexcept = delete;
	
	template<class Arg>
	void ToString(StringW &target, Arg arg) noexcept = delete;
	
	template<>
	void ToString(StringA &target, const CharW *arg) noexcept = delete;
	
	template<>
	void ToString(StringW &target, const CharA *arg) noexcept = delete;
	
	template<>
	inline void WHALE_API ToString(StringA &target, const CharA *arg) noexcept
	{
		target = arg;
	}
	
	template<>
	inline void WHALE_API ToString(StringW &target, const CharW *arg) noexcept
	{
		target = arg;
	}
	
	template<>
	inline void WHALE_API ToString(StringA &target, const StringA &arg) noexcept
	{
		target = arg;
	}
	
	template<>
	inline void WHALE_API ToString(StringW &target, const StringW &arg) noexcept
	{
		target = arg;
	}
	
	template<>
	inline void WHALE_API ToString(StringA &target, Bool arg) noexcept
	{
		target = arg ? "true" : "false";
	}
	
	template<>
	inline void WHALE_API ToString(StringW &target, Bool arg) noexcept
	{
		target = arg ? L"true" : L"false";
	}
	
}

