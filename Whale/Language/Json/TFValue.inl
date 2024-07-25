

namespace Whale::Json
{
	
	template<class CharT>
	TFValue<CharT>::TFValue() : TFValue(nullptr) {}
	
	template<class CharT>
	TFValue<CharT>::TFValue(NullPtrT) : type(ETypeNull), value() {}
	
	template<class CharT>
	TFValue<CharT>::TFValue(Bool value)
		: type(ETypeBool), value()
	{
		this->value.boolValue = value;
	}
	
	template<class CharT>
	TFValue<CharT>::TFValue(int32 value)
		: type(ETypeInt), value()
	{
		this->value.intValue = value;
	}
	
	template<class CharT>
	TFValue<CharT>::TFValue(int64 value)
		: type(ETypeInt), value()
	{
		this->value.intValue = value;
	}
	
	template<class CharT>
	TFValue<CharT>::TFValue(Double value)
		: type(ETypeDouble), value()
	{
		this->value.doubleValue = value;
	}
	
	template<class CharT>
	TFValue<CharT>::TFValue(const CharT *str)
		: type(ETypeString), value()
	{
		this->value.pString = WHALE_NEW_CLIENT String(str);
	}
	
	template<class CharT>
	TFValue<CharT>::TFValue(TFValue<CharT>::String str)
		: type(ETypeString), value()
	{
		this->value.pString = WHALE_NEW_CLIENT String(Whale::Move(str));
	}
	
	template<class CharT>
	TFValue<CharT>::TFValue(TFValue<CharT>::Array value)
		: type(ETypeArray), value()
	{
		this->value.pArray = WHALE_NEW_CLIENT Array(Whale::Move(value));
	}
	
	template<class CharT>
	TFValue<CharT>::TFValue(TFValue<CharT>::Object value)
		: type(ETypeObject), value()
	{
		this->value.pObject = WHALE_NEW_CLIENT Object(Whale::Move(value));
	}
	
	template<class CharT>
	NullPtrT TFValue<CharT>::AsNull() const
	{
		if (IsNull()) return nullptr;
		throw FInvalidCastException("can not cast to Null");
	}
	
	template<class CharT>
	Bool TFValue<CharT>::AsBool() const
	{
		if (IsBool()) return value.boolValue;
		throw FInvalidCastException("can not cast to Bool");
	}
	
	template<class CharT>
	int64 TFValue<CharT>::AsInt() const
	{
		if (IsInt()) return value.intValue;
		throw FInvalidCastException("can not cast to Int");
	}
	
	template<class CharT>
	Double TFValue<CharT>::AsDouble() const
	{
		if (IsDouble()) return value.doubleValue;
		throw FInvalidCastException("can not cast to Double");
	}
	
	template<class CharT>
	const typename TFValue<CharT>::String &TFValue<CharT>::AsString() const
	{
		if (IsString()) return *value.pString;
		throw FInvalidCastException("can not cast to String");
	}
	
	template<class CharT>
	const typename TFValue<CharT>::Array &TFValue<CharT>::AsArray() const
	{
		if (IsArray()) return *value.pArray;
		throw FInvalidCastException("can not cast to Array");
	}
	
	template<class CharT>
	const typename TFValue<CharT>::Object &TFValue<CharT>::AsObject() const
	{
		if (IsObject()) return *value.pObject;
		throw FInvalidCastException("can not cast to Object");
	}
	
	template<class CharT>
	const Bool *TFValue<CharT>::IfBool() const noexcept
	{
		return IsBool() ? &value.boolValue : nullptr;
	}
	
	template<class CharT>
	const int64 *TFValue<CharT>::IfInt() const noexcept
	{
		return IsInt() ? &value.intValue : nullptr;
	}
	
	template<class CharT>
	const Double *TFValue<CharT>::IfDouble() const noexcept
	{
		return IsDouble() ? &value.doubleValue : nullptr;
	}
	
	template<class CharT>
	const typename TFValue<CharT>::String *TFValue<CharT>::IfString() const noexcept
	{
		return IsString() ? value.pString : nullptr;
	}
	
	template<class CharT>
	const typename TFValue<CharT>::Array *TFValue<CharT>::IfArray() const noexcept
	{
		return IsArray() ? value.pArray : nullptr;
	}
	
	template<class CharT>
	const typename TFValue<CharT>::Object *TFValue<CharT>::IfObject() const noexcept
	{
		return IsObject() ? value.pObject : nullptr;
	}
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::At(SizeT index) noexcept
	{
		if (!IsArray()) operator=(ETypeArray);
		auto length = value.pArray->GetLength();
		if (index >= length)
		{
			for (auto i = length; i <= index; i++)
			{
				value.pArray->Append(TFValue<CharT>());
			}
		}
		return value.pArray->At(index);
	}
	
	template<class CharT>
	const TFValue<CharT> &TFValue<CharT>::At(SizeT index) const
	{
		if (!IsArray()) throw FInvalidCastException("this json is not a array");
		auto length = value.pArray->GetLength();
		if (index >= length)
		{
			for (auto i = length; i <= index; i++)
			{
				value.pArray->Append(TFValue<CharT>());
			}
		}
		return value.pArray->At(index);
	}
	
	template<class CharT>
	TFValue<CharT> &TFValue<CharT>::At(const String &key) noexcept
	{
		if (!IsObject()) operator=(ETypeObject);
		return value.pObject->operator[](key);
	}
	
	template<class CharT>
	const TFValue<CharT> &TFValue<CharT>::At(const String &key) const
	{
		if (!IsObject()) throw FInvalidCastException("this json is not a Object");
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
	TFValue<CharT> &TFValue<CharT>::operator=(EType eType)
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
	TFValue<CharT>::TFValue(EType type)
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
	
	template<class CharT>
	void TFValue<CharT>::Swap(TFValue &other) noexcept
	{
		Whale::Swap(this->type, other.type);
		Whale::Swap(this->value, other.value);
	}
	
	template<class CharT>
	Bool TFValue<CharT>::Equal(const TFValue &other) const noexcept
	{
		if (this->type != other.type) return false;
		switch (this->type)
		{
			case ETypeNull:
				return true;
			case ETypeBool:
				return this->value.boolValue == other.value.boolValue;
			case ETypeInt:
				return this->value.intValue == other.value.intValue;
			case ETypeDouble:
				return this->value.doubleValue == other.value.doubleValue;
			case ETypeString:
				return this->value.pString->Equal(*other.value.pString);
			case ETypeArray:
				return this->value.pArray->Equal(*other.value.pArray);
			case ETypeObject:
				return *this->value.pObject == *other.value.pObject;
			default:
				return false;
		}
	}
	
	template<class CharT>
	SizeT TFValue<CharT>::GetLength() const noexcept
	{
		switch (this->type)
		{
			case ETypeNull:
				return 1;
			case ETypeBool:
				return 1;
			case ETypeInt:
				return 1;
			case ETypeDouble:
				return 1;
			case ETypeString:
				return this->value.pString->GetLength();
			case ETypeArray:
				return this->value.pArray->GetLength();
			case ETypeObject:
				return this->value.pObject->size();
			default:
				return 0;
		}
	}
	
	template<class CharT>
	Bool TFValue<CharT>::Has(SizeT index) const noexcept
	{
		if (!IsArray()) return false;
		return index < this->value.pArray->GetLength();
	}
	
	template<class CharT>
	Bool TFValue<CharT>::Has(const TFValue::String &key) const noexcept
	{
		if (!IsObject()) return false;
		return this->value.pObject->find(key) != this->value.pObject->end();
	}
	
	template<class CharT>
	Bool TFValue<CharT>::Remove(SizeT index) noexcept
	{
		if (!IsArray()) return false;
		if (index >= this->value.pArray->GetLength()) return false;
		throw FException("TFValue<CharT>::Remove(SizeT) const failed");
	}
	
	template<class CharT>
	Bool TFValue<CharT>::Remove(const TFValue::String &key) noexcept
	{
		if (!IsObject()) return false;
		return this->value.pObject->erase(key) != 0;
	}
	
	template<>
	inline typename TFValue<CharA>::String WHALE_API TFValue<CharA>::ToString() const noexcept
	{
		String result;
		switch (this->type)
		{
			case ETypeNull:
				result += "null";
				break;
			case ETypeBool:
				result += this->value.boolValue ? "true" : "false";
				break;
			case ETypeInt:
				result += "int";
				break;
			case ETypeDouble:
				result += "double";
				break;
			case ETypeString:
				result += "\"";
				result += *this->value.pString;
				result += "\"";
				break;
			case ETypeArray:
			{
				result += "[";
				auto iter = this->value.pArray->Begin();
				if (iter != this->value.pArray->End())
				{
					result += iter->ToString();
					iter++;
				}
				for (; iter != this->value.pArray->End(); iter++)
				{
					result += ", ";
					result += iter->ToString();
				}
				result += "]";
				break;
			}
			case ETypeObject:
			{
				result += "{";
				auto iter = this->value.pObject->begin();
				if (iter != this->value.pObject->end())
				{
					result += "\"";
					result += iter->first;
					result += "\": ";
					result += iter->second.ToString();
					iter++;
				}
				for (; iter != this->value.pObject->end(); iter++)
				{
					result += ", \"";
					result += iter->first;
					result += "\": ";
					result += iter->second.ToString();
				}
				result += "}";
				break;
			}
			default:
				result += "<unknown>";
				break;
		}
		return result;
	}
	
	template<>
	inline typename TFValue<CharW>::String WHALE_API TFValue<CharW>::ToString() const noexcept
	{
		String result;
		switch (this->type)
		{
			case ETypeNull:
				result += L"null";
				break;
			case ETypeBool:
				result += this->value.boolValue ? L"true" : L"false";
				break;
			case ETypeInt:
				result += L"int";
				break;
			case ETypeDouble:
				result += L"double";
				break;
			case ETypeString:
				result += L"\"";
				result += *this->value.pString;
				result += L"\"";
				break;
			case ETypeArray:
			{
				result += L"[";
				auto iter = this->value.pArray->Begin();
				if (iter != this->value.pArray->End())
				{
					result += iter->ToString();
					iter++;
				}
				for (; iter != this->value.pArray->End(); iter++)
				{
					result += L", ";
					result += iter->ToString();
				}
				result += L"]";
				break;
			}
			case ETypeObject:
			{
				result += L"{";
				auto iter = this->value.pObject->begin();
				if (iter != this->value.pObject->end())
				{
					result += L"\"";
					result += iter->first;
					result += L"\": ";
					result += iter->second.ToString();
					iter++;
				}
				for (; iter != this->value.pObject->end(); iter++)
				{
					result += L", \"";
					result += iter->first;
					result += L"\": ";
					result += iter->second.ToString();
				}
				result += L"}";
				break;
			}
			default:
				result += L"<unknown>";
				break;
		}
		return result;
	}
	
	template<>
	inline typename TFValue<CharA>::String WHALE_API TFValue<CharA>::KeyToString(const String &key) const
	{
		String result{"\""};
		result += key;
		result += "\": ";
		result += At(key).ToString();
		return result;
	}
	
	template<>
	inline typename TFValue<CharW>::String WHALE_API TFValue<CharW>::KeyToString(const String &key) const
	{
		String result{L"\""};
		result += key;
		result += L"\": ";
		result += At(key).ToString();
		return result;
	}
}