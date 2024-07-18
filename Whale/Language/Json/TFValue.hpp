//
// Created by admin on 2024/7/18.
//

#pragma once

#include "Whale/Core/Tool/HTypeDef.hpp"
#include "Whale/Core/Container/TFString.hpp"
#include "Whale/Core/FException/FException.hpp"

#include <vector>
#include <map>

namespace Whale::Language::Json
{
	
	
	///
	/// Json值
	template<class CharT>
	class TFValue
	{
	public:
		
		///
		/// 类型
		enum EType
		{
			ETypeNull = 0,
			ETypeBool,
			ETypeInt,
			ETypeDouble,
			ETypeString,
			ETypeArray,
			ETypeObject
		};
		
		using String = TFString<CharT>;
		using Array = std::vector<TFValue>;
		using Object = std::map<String, TFValue>;
	
	public:
		
		TFValue() : TFValue(nullptr) {}
		
		explicit TFValue(NullPtrT) : type(ETypeNull), value() {}
		
		explicit TFValue(Bool value)
			: type(ETypeBool), value()
		{
			this->value.boolValue = value;
		}
		
		explicit TFValue(int32 value)
			: type(ETypeInt), value()
		{
			this->value.intValue = value;
		}
		
		explicit TFValue(int64 value)
			: type(ETypeInt), value()
		{
			this->value.intValue = value;
		}
		
		explicit TFValue(Double value)
			: type(ETypeDouble), value()
		{
			this->value.doubleValue = value;
		}
		
		explicit TFValue(const CharT *str)
			: type(ETypeString), value()
		{
			this->value.pString = WHALE_NEW_CLIENT String(str);
		}
		
		explicit TFValue(String str)
			: type(ETypeString), value()
		{
			this->value.pString = WHALE_NEW_CLIENT String(Whale::Move(str));
		}
		
		explicit TFValue(Array value)
			: type(ETypeArray), value()
		{
			this->value.pArray = WHALE_NEW_CLIENT Array(Whale::Move(value));
		}
		
		explicit TFValue(Object value)
			: type(ETypeObject), value()
		{
			this->value.pObject = WHALE_NEW_CLIENT Object(Whale::Move(value));
		}
		
		explicit TFValue(EType type);
		
		TFValue(const TFValue &other);
		
		TFValue(TFValue &&other) noexcept: TFValue() { Swap(other); }
		
		~TFValue() noexcept;
	
	public:
		
		TFValue &operator=(NullPtrT);
		
		TFValue &operator=(Bool aBool);
		
		TFValue &operator=(int32 i);
		
		TFValue &operator=(int64 i);
		
		TFValue &operator=(Double aDouble);
		
		TFValue &operator=(const CharT *str);
		
		TFValue &operator=(String str);
		
		TFValue &operator=(Array array);
		
		TFValue &operator=(Object object);
		
		TFValue &operator=(EType eType);
		
		TFValue &operator=(const TFValue &other);
		
		TFValue &operator=(TFValue &&other) noexcept;
		
		TFValue &operator[](SizeT index) noexcept { return At(index); }
		
		const TFValue &operator[](SizeT index) const noexcept { return At(index); }
		
		TFValue &operator[](const String &key) noexcept { return At(key); }
		
		const TFValue &operator[](const String &key) const noexcept { return At(key); }
	
	public:
		
		[[nodiscard]] Bool Is(EType eType) const noexcept { return GetType() == eType; }
		
		[[nodiscard]] Bool IsNull() const noexcept { return Is(ETypeNull); }
		
		[[nodiscard]] Bool IsBool() const noexcept { return Is(ETypeBool); }
		
		[[nodiscard]] Bool IsInt() const noexcept { return Is(ETypeInt); }
		
		[[nodiscard]] Bool IsDouble() const noexcept { return Is(ETypeDouble); }
		
		[[nodiscard]] Bool IsString() const noexcept { return Is(ETypeString); }
		
		[[nodiscard]] Bool IsArray() const noexcept { return Is(ETypeArray); }
		
		[[nodiscard]] Bool IsObject() const noexcept { return Is(ETypeObject); }
		
		[[nodiscard]] NullPtrT AsNull() const
		{
			if (IsNull()) return nullptr;
			throw FInvalidCastException("can not cast to Null");
		}
		
		[[nodiscard]] Bool AsBool() const
		{
			if (IsBool()) return value.boolValue;
			throw FInvalidCastException("can not cast to Bool");
		}
		
		[[nodiscard]] int64 AsInt() const
		{
			if (IsInt()) return value.intValue;
			throw FInvalidCastException("can not cast to Int");
		}
		
		[[nodiscard]] Double AsDouble() const
		{
			if (IsDouble()) return value.doubleValue;
			throw FInvalidCastException("can not cast to Double");
		}
		
		[[nodiscard]] const String &AsString() const
		{
			if (IsString()) return *value.pString;
			throw FInvalidCastException("can not cast to String");
		}
		
		[[nodiscard]] const Array &AsArray() const
		{
			if (IsArray()) return *value.pArray;
			throw FInvalidCastException("can not cast to Array");
		}
		
		[[nodiscard]] const Object &AsObject() const
		{
			if (IsObject()) return *value.pObject;
			throw FInvalidCastException("can not cast to Object");
		}
		
		[[nodiscard]] const Bool *IfBool() const noexcept
		{
			return IsBool() ? &value.boolValue : nullptr;
		}
		
		[[nodiscard]] const int64 *IfInt() const noexcept
		{
			return IsInt() ? &value.intValue : nullptr;
		}
		
		[[nodiscard]] const Double *IfDouble() const noexcept
		{
			return IsDouble() ? &value.doubleValue : nullptr;
		}
		
		[[nodiscard]] const String *IfString() const noexcept
		{
			return IsString() ? value.pString : nullptr;
		}
		
		[[nodiscard]] const Array *IfArray() const noexcept
		{
			return IsArray() ? value.pArray : nullptr;
		}
		
		[[nodiscard]] const Object *IfObject() const noexcept
		{
			return IsObject() ? value.pObject : nullptr;
		}
		
		TFValue &At(SizeT index) noexcept;
		
		const TFValue &At(SizeT index) const noexcept;
		
		TFValue &At(const String &key) noexcept;
		
		const TFValue &At(const String &key) const noexcept;
	
	public:
		
		
		void Swap(TFValue &other) noexcept
		{
			Whale::Swap(this->type, other.type);
			Whale::Swap(this->value, other.value);
		}
	
	public:
		
		[[nodiscard]]
		EType GetType() const noexcept { return type; }
	
	private:
		
		union UValue
		{
			Bool boolValue;
			int64 intValue;
			Double doubleValue;
			String *pString;
			Array *pArray;
			Object *pObject;
		};
	
	private:
		
		EType type;
		
		UValue value;
		
	};
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::At(SizeT index) noexcept
	{
		if (!IsArray()) operator=(ETypeArray);
		auto length = value.pArray->size();
		if (index >= length)
		{
			for (auto i = length; i <= index; i++)
			{
				value.pArray->emplace_back();
			}
		}
		return value.pArray->at(index);
	}
	
	template<class CharT>
	const TFValue<CharT> &TFValue<CharT>::At(SizeT index) const noexcept
	{
		if (!IsArray()) operator=(ETypeArray);
		auto length = value.pArray->size();
		if (index >= length)
		{
			for (auto i = length; i <= index; i++)
			{
				value.pArray->emplace_back();
			}
		}
		return value.pArray->at(index);
	}
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::At(const String &key) noexcept
	{
		if (!IsObject()) operator=(ETypeObject);
		return value.pObject->operator[](key);
	}
	
	template<class CharT>
	const TFValue<CharT> &TFValue<CharT>::At(const String &key) const noexcept
	{
		if (!IsObject()) operator=(ETypeObject);
		return value.pObject->operator[](key);
	}
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::operator=(TFValue &&other) noexcept
	{
		TFValue(Whale::Move(other)).Swap(*this);
		return *this;
	}
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::operator=(const TFValue &other)
	{
		TFValue(other).Swap(*this);
		return *this;
	}
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::operator=(TFValue::EType eType)
	{
		TFValue(eType).Swap(*this);
		return *this;
	}
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::operator=(TFValue::Object object)
	{
		TFValue(Whale::Move(object)).Swap(*this);
		return *this;
	}
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::operator=(TFValue::Array array)
	{
		TFValue(Whale::Move(array)).Swap(*this);
		return *this;
	}
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::operator=(TFValue::String str)
	{
		TFValue(Whale::Move(str)).Swap(*this);
		return *this;
	}
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::operator=(const CharT *str)
	{
		TFValue(str).Swap(*this);
		return *this;
	}
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::operator=(Double aDouble)
	{
		TFValue(aDouble).Swap(*this);
		return *this;
	}
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::operator=(int64 i)
	{
		TFValue(i).Swap(*this);
		return *this;
	}
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::operator=(int32 i)
	{
		TFValue(i).Swap(*this);
		return *this;
	}
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::operator=(Bool aBool)
	{
		TFValue(aBool).Swap(*this);
		return *this;
	}
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::operator=(NullPtrT)
	{
		TFValue(nullptr).Swap(*this);
		return *this;
	}
	
	template<class CharT>
	TFValue<CharT>::~TFValue() noexcept
	{
		switch (this->type)
		{
			case ETypeString:
				delete this->value.pString;
				break;
			case ETypeArray:
				delete this->value.pArray;
				break;
			case ETypeObject:
				delete this->value.pObject;
				break;
			case ETypeNull:
			case ETypeBool:
			case ETypeInt:
			case ETypeDouble:
			default:
				break;
		}
		this->type = ETypeNull;
	}
	
	template<class CharT>
	TFValue<CharT>::TFValue(const TFValue &other)
		: type(other.type), value()
	{
		switch (this->type)
		{
			case ETypeNull:
				break;
			case ETypeBool:
				this->value.boolValue = other.value.boolValue;
				break;
			case ETypeInt:
				this->value.intValue = other.value.intValue;
				break;
			case ETypeDouble:
				this->value.doubleValue = other.value.doubleValue;
				break;
			case ETypeString:
				this->value.pString = WHALE_NEW_CLIENT String(*other.value.pString);
				break;
			case ETypeArray:
				this->value.pArray = WHALE_NEW_CLIENT Array(*other.value.pArray);
				break;
			case ETypeObject:
				this->value.pObject = WHALE_NEW_CLIENT Object(*other.value.pObject);
				break;
			default:
				this->type = ETypeNull;
				break;
		}
	}
	
	template<class CharT>
	TFValue<CharT>::TFValue(TFValue::EType type)
		: type(type), value()
	{
		switch (type)
		{
			case ETypeNull:
				break;
			case ETypeBool:
				this->value.boolValue = false;
				break;
			case ETypeInt:
				this->value.intValue = 0;
				break;
			case ETypeDouble:
				this->value.doubleValue = 0.0;
				break;
			case ETypeString:
				this->value.pString = WHALE_NEW_CLIENT String();
				break;
			case ETypeArray:
				this->value.pArray = WHALE_NEW_CLIENT Array();
				break;
			case ETypeObject:
				this->value.pObject = WHALE_NEW_CLIENT Object();
				break;
			default:
				this->type = ETypeNull;
				break;
		}
	}
	
	using JsonA = TFValue<Char>;
	using JsonW = TFValue<WChar>;
	using JsonT = TFValue<TChar>;
	
} // Whale
