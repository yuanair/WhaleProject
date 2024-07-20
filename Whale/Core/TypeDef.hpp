//
// Created by admin on 2024/6/16.
//

#pragma once

// compiler

#define WHALE_COMPILER_TYPE_UNKNOWN 0
#define WHALE_COMPILER_TYPE_MSVC 1
#define WHALE_COMPILER_TYPE_GCC 2
#define WHALE_COMPILER_TYPE_CLANG 3

#define WHALE_COMPILER_BIT_UNKNOWN 0
#define WHALE_COMPILER_BIT_32 32
#define WHALE_COMPILER_BIT_64 64

#define WHALE_TARGET_UNKNOWN 0
#define WHALE_TARGET_WINDOWS 1
#define WHALE_TARGET_LINUX 2
#define WHALE_TARGET_MACOS 3
#define WHALE_TARGET_IOS 4
#define WHALE_TARGET_ANDROID 5

#if defined(_MSC_VER)
	#define WHALE_COMPILER_TYPE WHALE_COMPILER_TYPE_MSVC
#elif defined(__GNUC__)
#define WHALE_COMPILER_TYPE WHALE_COMPILER_TYPE_GCC
#else
	#define WHALE_COMPILER_TYPE WHALE_COMPILER_TYPE_UNKNOWN
#endif

#if defined(_WIN32)
	#define WHALE_TARGET WHALE_TARGET_WINDOWS
#if defined(_WIN64)
	#define WHALE_COMPILER_BIT WHALE_COMPILER_BIT_64
#else
	#define WHALE_COMPILER_BIT WHALE_COMPILER_BIT_32
#endif
#elif defined(__APPLE__)
#include "TargetConditionals.h"
	#if defined(TARGET_OS_IPHONE)
		#define WHALE_TARGET WHALE_TARGET_IOS
	#elif defined(TARGET_OS_MAC)
		#define WHALE_TARGET WHALE_TARGET_MACOS
	#else
		#define WHALE_TARGET WHALE_TARGET_UNKNOWN
		#error "Unknown Apple platform"
	#endif
	#define WHALE_COMPILER_BIT WHALE_COMPILER_BIT_64
#elif __ANDROID__
	#define WHALE_TARGET WHALE_TARGET_ANDROID
#if defined(__x86_64__)
	#define WHALE_COMPILER_BIT WHALE_COMPILER_BIT_64
#elif defined(__i386__)
	#define WHALE_COMPILER_BIT WHALE_COMPILER_BIT_32
#else
	#define WHALE_COMPILER_BIT WHALE_COMPILER_BIT_UNKNOWN
#endif
#elif __linux__
	#define WHALE_TARGET WHALE_TARGET_LINUX
#if defined(__x86_64__)
	#define WHALE_COMPILER_BIT WHALE_COMPILER_BIT_64
#elif defined(__i386__)
	#define WHALE_COMPILER_BIT WHALE_COMPILER_BIT_32
#else
	#define WHALE_COMPILER_BIT WHALE_COMPILER_BIT_UNKNOWN
#endif
#else
	#define WHALE_TARGET WHALE_TARGET_UNKNOWN
#error "Unknown platform"
#endif

// UNICODE

#define WHALE_WIDE_(s) L ## s
#define WHALE_WIDE(s) WHALE_WIDE_(s)

#if defined(UNICODE) || defined(_UNICODE)
	#define WHALE_UNICODE
	#define WHALE_TEXT(s) WHALE_WIDE_(s)
#else
	#define WHALE_TEXT(s) s
#endif

// assert

#ifdef _DEBUG
#define WHALE_ASSERT(expression) ((!!(expression)) || (::Whale::FatalMessage(WHALE_WIDE(#expression), WHALE_WIDE(__FILE__), __LINE__, WHALE_WIDE(__FUNCSIG__)), 0))
#else
#define WHALE_ASSERT(expression) ((void)0)
#endif

// WHALE_API

#ifndef WHALE_API

#define WHALE_API __declspec(dllexport)

#else

#ifdef _DLL
#define WHALE_API __declspec(dllimport)
#else
#define WHALE_API
#endif

#endif

// newline

#if WHALE_TARGET == WHALE_TARGET_WINDOWS
#define WHALE_NEWLINE '\r', '\n'
#elif WHALE_TARGET == WHALE_TARGET_MACOS
#define WHALE_NEWLINE '\r'
#else
#define WHALE_NEWLINE '\n'
#endif


namespace Whale
{
	
	using Byte = char;
	
	using Short = short;
	
	using Int = int;
	
	using Long = long;
	
	using LongLong = long long;
	
	using UByte = unsigned char;
	
	using UShort = unsigned short;
	
	using UInt = unsigned int;
	
	using ULong = unsigned long;
	
	using ULongLong = unsigned long long;
	
	using CharA = char;
	
	using CharW = wchar_t;
	
	using Float = float;
	
	using Double = double;
	
	using Bool = bool;
	
	using NullPtrT = decltype(nullptr);
	
	#if WHALE_COMPILER_TYPE == WHALE_COMPILER_TYPE_MSVC || WHALE_COMPILER_TYPE == WHALE_COMPILER_TYPE_CLANG
	
	using int8 = __int8;
	
	using int16 = __int16;
	
	using int32 = __int32;
	
	using int64 = __int64;
	
	using uint8 = unsigned __int8;
	
	using uint16 = unsigned __int16;
	
	using uint32 = unsigned __int32;
	
	using uint64 = unsigned __int64;
	
	#elif WHALE_COMPILER_TYPE == WHALE_COMPILER_TYPE_GCC
	using int8 = Byte;
	
	using int16 = Short;
	
	using int32 = Int;
	
	using int64 = LongLong;
	
	using uint8 = UByte;
	
	using uint16 = UShort;
	
	using uint32 = UInt;
	
	using uint64 = ULongLong;
	
	#endif
	
	#if WHALE_COMPILER_BIT == WHALE_COMPILER_BIT_64
	
	using IntPointer = int64;
	
	using UIntPointer = uint64;
	
	using LongPointer = int64;
	
	using ULongPointer = uint64;
	
	#elif WHALE_COMPILER_BIT == WHALE_COMPILER_BIT_32
	
	using IntPointer = Int;
	
	using UIntPointer = UInt;
	
	using LongPointer = Long;
	
	using ULongPointer = ULong;
	
	#endif
	
	using SizeT = uint64;

#if defined(UNICODE) || defined(_UNICODE)
	using CharT = CharW;
#else
	using CharT = CharA;
#endif
	
	constexpr const CharA WhaleTagA[] = "Whale";
	constexpr const CharW WhaleTagW[] = L"Whale";

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
	WHALE_API void FatalMessage(const CharW *message, const CharW *file, uint64 line, const CharW *function);
	
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
		inline TPoint2<T> GetCenterPoint() const noexcept
		{
			return TPoint2<T>{x + width / T{2}, y + height / T{2}};
		}
		
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
