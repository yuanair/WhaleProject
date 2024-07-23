//
// Created by admin on 2024/7/23.
//

#pragma once

#include "TypeDef.hpp"

namespace Whale
{
#pragma region RemoveConst
	
	template<class T>
	struct RemoveConst
	{
		using Type = T;
	};
	
	template<class T>
	struct RemoveConst<const T>
	{
		using Type = T;
	};
	
	template<typename T>
	using RemoveConstType = typename RemoveConst<T>::Type;

#pragma endregion

#pragma region RemoveVolatile
	
	template<class T>
	struct RemoveVolatile
	{
		using Type = T;
	};
	
	template<class T>
	struct RemoveVolatile<volatile T>
	{
		using Type = T;
	};
	
	template<typename T>
	using RemoveVolatileType = typename RemoveVolatile<T>::Type;

#pragma endregion

#pragma region RemovePoint
	
	template<class T>
	struct RemovePoint
	{
		using Type = T;
	};
	
	template<class T>
	struct RemovePoint<T *>
	{
		using Type = T;
	};
	
	template<class T>
	struct RemovePoint<T *const>
	{
		using Type = T;
	};
	
	template<class T>
	struct RemovePoint<T *volatile>
	{
		using Type = T;
	};
	
	template<class T>
	struct RemovePoint<T *const volatile>
	{
		using Type = T;
	};
	
	template<typename T>
	using RemovePointType = typename RemovePoint<T>::Type;

#pragma endregion

#pragma region RemoveReference
	
	template<class T>
	struct RemoveReference
	{
		using Type = T;
		using ConstRefType = const T;
	};
	
	template<class T>
	struct RemoveReference<T &>
	{
		using Type = T;
		using ConstRefType = const T &;
	};
	
	template<class T>
	struct RemoveReference<T &&>
	{
		using Type = T;
		using ConstRefType = const T &&;
	};
	
	template<typename T>
	using RemoveReferenceType = typename RemoveReference<T>::Type;

#pragma endregion

#pragma region Constant
	
	template<class ValueT, ValueT Value>
	struct IntegralConstant
	{
		static constexpr ValueT value = Value;
		
		using ValueType = ValueT;
		using Type = IntegralConstant;
		
		constexpr operator ValueType() const noexcept // NOLINT(*-explicit-constructor)
		{
			return value;
		}
		
		constexpr ValueType operator()() const noexcept
		{
			return value;
		}
	};
	
	template<Bool Value>
	using BoolConstant = IntegralConstant<Bool, Value>;
	
	using TrueType = BoolConstant<true>;
	using FalseType = BoolConstant<false>;

#pragma endregion

#pragma region IsXXX
	
	// union
	
	template<class T>
	struct IsUnion : BoolConstant<__is_union(T)> {};
	
	template<typename T>
	inline constexpr Bool IsUnionValue = __is_union(T);
	
	// class
	
	template<class T>
	struct IsClass : BoolConstant<__is_class(T)> {};
	
	template<typename T>
	inline constexpr Bool IsClassValue = __is_class(T);
	
	// enum
	
	template<class T>
	struct IsEnum : BoolConstant<__is_enum(T)> {};
	
	template<typename T>
	inline constexpr Bool IsEnumValue = __is_enum(T);
	
	// empty
	
	template<class T>
	struct IsEmpty : BoolConstant<__is_empty(T)> {};
	
	template<typename T>
	inline constexpr Bool IsEmptyValue = __is_empty(T);
	
	// abstract
	
	template<class T>
	struct IsAbstract : BoolConstant<__is_abstract(T)> {};
	
	template<typename T>
	inline constexpr Bool IsAbstractValue = __is_abstract(T);
	
	// final
	
	template<class T>
	struct IsFinal : BoolConstant<__is_final(T)> {};
	
	template<typename T>
	inline constexpr Bool IsFinalValue = __is_final(T);
	
	// same

#ifdef __clang__
	
	template <class T1, class T2>
	inline constexpr Bool IsSameValue = __is_same(T1, T2);

	template <class T1, class T2>
	struct IsSame : BoolConstant<__is_same(T1, T2)> {};

#else
	
	template<class, class>
	inline constexpr Bool IsSameValue = false;
	template<class T>
	inline constexpr Bool IsSameValue<T, T> = true;
	
	template<class T1, class T2>
	struct IsSame : BoolConstant<IsSameValue<T1, T2>> {};

#endif
	
	// base of
	
	template<class Base, class T>
	struct IsBaseOf : BoolConstant<__is_base_of(Base, T)> {};
	
	template<typename Base, class T>
	inline constexpr Bool IsBaseOfValue = __is_base_of(Base, T);
	
	// left value reference
	
	template<class>
	inline constexpr Bool IsLValueReferenceValue = false; // determine whether type argument is an lvalue reference
	
	template<class T>
	inline constexpr Bool IsLValueReferenceValue<T &> = true;
	
	template<class T>
	struct IsLValueReference : BoolConstant<IsLValueReferenceValue<T>> {};
	
	// right value reference
	
	template<class>
	inline constexpr Bool IsRValueReferenceValue = false;
	
	template<class T>
	inline constexpr Bool IsRValueReferenceValue<T &&> = true;
	
	template<class T>
	struct IsRValueReference : BoolConstant<IsRValueReferenceValue<T>> {};
	
	// reference
	
	template<class>
	inline constexpr Bool IsReferenceValue = false;
	
	template<class T>
	inline constexpr Bool IsReferenceValue<T &> = true;
	
	template<class T>
	inline constexpr Bool IsReferenceValue<T &&> = true;
	
	template<class T>
	struct IsReference : BoolConstant<IsReferenceValue<T>> {};
	
	// pointer
	
	template<class>
	inline constexpr Bool IsPointerValue = false;
	
	template<class T>
	inline constexpr Bool IsPointerValue<T *> = true;
	
	template<class T>
	inline constexpr Bool IsPointerValue<T *const> = true;
	
	template<class T>
	inline constexpr Bool IsPointerValue<T *volatile> = true;
	
	template<class T>
	inline constexpr Bool IsPointerValue<T *const volatile> = true;
	
	template<class T>
	struct IsPointer : BoolConstant<IsPointerValue<T>> {};

#pragma endregion
	
	template<Bool Test, class T = void>
	struct EnableIf {};
	
	template<class T>
	struct EnableIf<true, T>
	{
		using type = T;
	};
	
	template<Bool Test, class T = void>
	using EnableIfType = typename EnableIf<Test, T>::type;
	
	template<typename T>
	WHALE_API constexpr T &&Forward(RemoveReferenceType<T> &arg) noexcept
	{
		return static_cast<T &&>(arg);
	}
	
	template<typename T>
	WHALE_API constexpr T &&Forward(RemoveReferenceType<T> &&arg) noexcept
	{
		static_assert(!IsLValueReferenceValue<T>, "bad Forward call");
		return static_cast<T &&>(arg);
	}
	
	template<typename T>
	WHALE_API constexpr RemoveReferenceType<T> &&Move(T &&arg) noexcept
	{
		return static_cast<RemoveReferenceType<T> &&>(arg);
	}
	
	template<typename T>
	inline WHALE_API void Swap(T &a, T &b) noexcept
	{
		T temp = Move(a);
		a = Move(b);
		b = Move(temp);
	}
	
} // Whale
