//
// Created by admin on 2024/7/18.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"
#include "Whale/Core/Container/TFString.hpp"
#include "Whale/Core/Exception.hpp"

#include <map>

namespace Whale::Json
{
	constexpr const CharA TagA[] = "Whale::Json";
	constexpr const CharW TagW[] = L"Whale::Json";
	
	///
	/// Json类型
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
	
	///
	/// Json值
	template<class CharT>
	class TFValue
	{
	public:
		
		using String = Container::TFString<CharT>;
		using Array = Container::TFArray<TFValue>;
		using Object = std::map<String, TFValue>;
	
	public:
		
		TFValue();
		
		explicit TFValue(NullPtrT);
		
		explicit TFValue(Bool value);
		
		explicit TFValue(int32 value);
		
		explicit TFValue(int64 value);
		
		explicit TFValue(Double value);
		
		explicit TFValue(const CharT *str);
		
		explicit TFValue(String str);
		
		explicit TFValue(Array value);
		
		explicit TFValue(Object value);
		
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
		
		Bool operator==(const TFValue &other) const noexcept { return Equal(other); }
		
		Bool operator!=(const TFValue &other) const noexcept { return !Equal(other); }
	
	public:
		
		[[nodiscard]] Bool Is(EType eType) const noexcept { return GetType() == eType; }
		
		[[nodiscard]] Bool IsNull() const noexcept { return Is(ETypeNull); }
		
		[[nodiscard]] Bool IsBool() const noexcept { return Is(ETypeBool); }
		
		[[nodiscard]] Bool IsInt() const noexcept { return Is(ETypeInt); }
		
		[[nodiscard]] Bool IsDouble() const noexcept { return Is(ETypeDouble); }
		
		[[nodiscard]] Bool IsString() const noexcept { return Is(ETypeString); }
		
		[[nodiscard]] Bool IsArray() const noexcept { return Is(ETypeArray); }
		
		[[nodiscard]] Bool IsObject() const noexcept { return Is(ETypeObject); }
		
		[[nodiscard]] NullPtrT AsNull() const;
		
		[[nodiscard]] Bool AsBool() const;
		
		[[nodiscard]] int64 AsInt() const;
		
		[[nodiscard]] Double AsDouble() const;
		
		[[nodiscard]] const String &AsString() const;
		
		[[nodiscard]] const Array &AsArray() const;
		
		[[nodiscard]] const Object &AsObject() const;
		
		[[nodiscard]] const Bool *IfBool() const noexcept;
		
		[[nodiscard]] const int64 *IfInt() const noexcept;
		
		[[nodiscard]] const Double *IfDouble() const noexcept;
		
		[[nodiscard]] const String *IfString() const noexcept;
		
		[[nodiscard]] const Array *IfArray() const noexcept;
		
		[[nodiscard]] const Object *IfObject() const noexcept;
		
		TFValue &At(SizeT index) noexcept;
		
		[[nodiscard]] const TFValue &At(SizeT index) const;
		
		TFValue &At(const String &key) noexcept;
		
		const TFValue &At(const String &key) const;
		
		///
		/// String, Array, Object: 获取长度
		/// Null, Bool, Int, Double: 1
		/// failed: 0
		/// \return 长度
		[[nodiscard]] SizeT GetLength() const noexcept;
		
		[[nodiscard]] Bool Has(SizeT index) const noexcept;
		
		[[nodiscard]] Bool Has(const String &key) const noexcept;
		
		[[nodiscard]] Bool Remove(SizeT index) const noexcept;
		
		[[nodiscard]] Bool Remove(const String &key) const noexcept;
		
		///
		/// \return json格式字符串
		[[nodiscard]] String ToString() const noexcept;
		
		///
		/// \return json格式键值对
		[[nodiscard]] String KeyToString(const String &key) const;
	
	public:
		
		
		void Swap(TFValue &other) noexcept;
		
		[[nodiscard]] Bool Equal(const TFValue &other) const noexcept;
	
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
	
	
	using JsonA = TFValue<CharA>;
	using JsonW = TFValue<CharW>;
	using JsonT = TFValue<CharT>;
	
} // Whale

#include "TFValue.inl"
