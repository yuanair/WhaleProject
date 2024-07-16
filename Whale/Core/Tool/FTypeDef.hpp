//
// Created by admin on 2024/6/16.
//

#pragma once

#define WHALE_WIDE_(s) L ## s
#define WHALE_WIDE(s) WHALE_WIDE_(s)

#ifdef _DEBUG
#define WHALE_ASSERT(expression) ((!!(expression)) || (::Whale::FatalMessage(WHALE_WIDE(#expression), WHALE_WIDE(__FILE__), __LINE__, WHALE_WIDE(__FUNCSIG__)), 0))
#else
#define WHALE_ASSERT(expression) ((void)0)
#endif

#ifndef WHALE_API

#define WHALE_API __declspec(dllexport)

#else

#ifdef _DLL
#define WHALE_API __declspec(dllimport)
#else
#define WHALE_API
#endif

#endif

namespace Whale
{
	
	using int8 = char;
	
	using int16 = short;
	
	using int32 = int;
	
	using int64 = long long;
	
	using uint8 = unsigned char;
	
	using uint16 = unsigned short;
	
	using uint32 = unsigned int;
	
	using uint64 = unsigned long long;
	
	using intptr = int64;
	
	using uintptr = uint64;
	
	using Char = char;
	
	using WChar = wchar_t;

#ifdef UNICODE
	using TChar = WChar;
#else
	using TChar = Char;
#endif
	
	using SizeT = uint64;
	
	using Float = float;
	
	using Double = double;
	
	using Bool = bool;
	
	using NullPtrT = decltype(__nullptr);


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
		
		constexpr operator ValueType() const noexcept
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
	
	// 致命消息
	WHALE_API void FatalMessage(const WChar *message, const WChar *file, uint64 line, const WChar *function);
	
	///
	/// 点
	/// \tparam T 类型
	template<class T>
	struct WHALE_API  TPoint2
	{
		/// 横坐标
		T x;
		
		/// 纵坐标
		T y;
	};
	
	
	///
	/// 大小
	/// \tparam T 类型
	template<class T>
	struct WHALE_API TSize2
	{
		/// 宽
		T width;
		
		/// 高
		T height;
	};
	
	
	///
	/// 点
	/// \tparam T 类型
	template<class T>
	struct WHALE_API TPoint3
	{
		/// 前后向坐标
		T x;
		
		/// 左右向坐标
		T y;
		
		/// 垂直坐标
		T z;
	};
	
	
	///
	/// 大小
	/// \tparam T 类型
	template<class T>
	struct WHALE_API TSize3
	{
		///
		T x;
		
		///
		T y;
		
		///
		T z;
	};
	
	
	///
	/// 矩形
	/// \tparam T 类型
	template<class T>
	struct WHALE_API TRect
	{
		/// 横坐标
		T x;
		
		/// 纵坐标
		T y;
		
		/// 宽
		T width;
		
		/// 高
		T height;
		
		///
		/// \return 位置
		inline TPoint2<T> GetPoint() const noexcept { return TPoint2<T>{x, y}; }
		
		///
		/// \param point 位置
		inline void SetPoint(const TPoint2<T> &point) const noexcept
		{
			x = point.x;
			y = point.y;
		}
		
		///
		/// \return 中心点
		inline TPoint2<T> GetCenterPoint() const noexcept { return TPoint2<T>{x + width / T{2}, y + height / T{2}}; }
		
		///
		/// \param centerPoint 中心点
		inline void SetCenterPoint(const TPoint2<T> &centerPoint) const noexcept
		{
			x = centerPoint.x - width / T{2};
			y = centerPoint.y - height / T{2};
		}
		
		///
		/// \return 大小
		inline TSize2<T> GetSize() const noexcept { return TSize2<T>{width, height}; }
		
		///
		/// \param size 位置
		inline void SetSize(const TSize2<T> &size) const noexcept
		{
			width = size.width;
			height = size.height;
		}
		
	};
	
	typedef TRect<int32> FRectI;
	typedef TRect<uint32> FRectU;
	typedef TRect<Float> FRectF;
	typedef TRect<Double> FRectD;
	
	typedef TPoint2<int32> FPoint2I;
	typedef TPoint2<uint32> FPoint2U;
	typedef TPoint2<Float> FPoint2F;
	typedef TPoint2<Double> FPoint2D;
	
	typedef TSize2<int32> FSize2I;
	typedef TSize2<uint32> FSize2U;
	typedef TSize2<Float> FSize2F;
	typedef TSize2<Double> FSize2D;
	
	typedef TPoint3<int32> FPoint3I;
	typedef TPoint3<uint32> FPoint3U;
	typedef TPoint3<Float> FPoint3F;
	typedef TPoint3<Double> FPoint3D;
	
	typedef TSize3<int32> FSize3I;
	typedef TSize3<uint32> FSize3U;
	typedef TSize3<Float> FSize3F;
	typedef TSize3<Double> FSize3D;
	
	
} // Whale
