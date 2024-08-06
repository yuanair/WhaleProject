//
// Created by admin on 2024/6/16.
//

#pragma once

// compiler

#if defined(_MSC_VER)
	#define WHALE_COMPILER_TYPE_MSVC
#elif defined(__GNUC__)
#define WHALE_COMPILER_TYPE_GCC
#else
	#error "Unknown compiler"
#endif

#if defined(_WIN32)
	#define WHALE_TARGET_WINDOWS
	#define WHALE_COMPILER_BIT_32
#if defined(_WIN64)
	#define WHALE_COMPILER_BIT_64
#endif
#elif defined(__APPLE__)
#include "TargetConditionals.h"
	#if defined(TARGET_OS_IPHONE)
		#define WHALE_TARGET_IOS
	#elif defined(TARGET_OS_MAC)
		#define WHALE_TARGET_MACOS
	#else
		#error "Unknown Apple platform"
	#endif
	#define WHALE_COMPILER_BIT_32
	#define WHALE_COMPILER_BIT_64
#elif __ANDROID__
	#define WHALE_TARGET_ANDROID
#if defined(__x86_64__)
	#define WHALE_COMPILER_BIT_32
	#define WHALE_COMPILER_BIT_64
#elif defined(__i386__)
	#define WHALE_COMPILER_BIT_32
#endif
#elif __linux__
	#define WHALE_TARGET_LINUX
#if defined(__x86_64__)
	#define WHALE_COMPILER_BIT_32
	#define WHALE_COMPILER_BIT_64
#elif defined(__i386__)
	#define WHALE_COMPILER_BIT_32
#endif
#else
	#define WHALE_TARGET_UNKNOWN
#error "Unknown platform"
#endif

// UNICODE

#define WHALE_WIDE_(s) L ## s
#define WHALE_STRING(s) #s
#define WHALE_WIDE(s) WHALE_WIDE_(s)

#define WTEXT(s) WHALE_WIDE_(s)

// Poor readability
// #define WHALE_TEXT_FROM_TYPE(type, s) ((type*)(::Whale::IsSameValue<type, ::Whale::CharW>) ? (::Whale::CharA*)(WHALE_WIDE_(s)) : (::Whale::CharA*)(s))


#if defined(UNICODE) || defined(_UNICODE)
	#define WHALE_UNICODE
	#define WHALE_TEXT(s) WHALE_WIDE_(s)
#else
	#define WHALE_TEXT(s) s
#endif

// assert

#if defined(DEBUG) || defined(_DEBUG)
#define WHALE_ASSERT(expression) ((!!(expression)) || (::Whale::Assert(WHALE_STRING(expression), __FILE__, __LINE__, __FUNCSIG__), 0))
#else
#define WHALE_ASSERT(expression) ((void)0)
#endif

// WHALE_API

#ifndef WHALE_API
	
	#ifdef _WIN32

#define WHALE_API __declspec(dllexport)
	
	#else

#define WHALE_API
	
	#endif

#else

#ifdef _DLL
#define WHALE_API __declspec(dllimport)
#else
#define WHALE_API
#endif

#endif

// newline

#ifdef WHALE_TARGET_WINDOWS
#define WHALE_NEWLINE '\r', '\n'
#elif defined(WHALE_TARGET_MACOS)
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
	
	using LongDouble = long double;
	
	using Bool = bool;
	
	using NullPtrT = decltype(nullptr);
	
	#if defined(WHALE_COMPILER_TYPE_MSVC) || defined(WHALE_COMPILER_TYPE_CLANG)
	
	using int8 = __int8;
	
	using int16 = __int16;
	
	using int32 = __int32;
	
	using int64 = __int64;
	
	using uint8 = unsigned __int8;
	
	using uint16 = unsigned __int16;
	
	using uint32 = unsigned __int32;
	
	using uint64 = unsigned __int64;
	
	#elif defined(WHALE_COMPILER_TYPE_GCC)
	using int8 = Byte;
	
	using int16 = Short;
	
	using int32 = Int;
	
	using int64 = LongLong;
	
	using uint8 = UByte;
	
	using uint16 = UShort;
	
	using uint32 = UInt;
	
	using uint64 = ULongLong;
	
	#endif
	
	#if defined(WHALE_COMPILER_BIT_64)
	
	using IntPointer = int64;
	
	using UIntPointer = uint64;
	
	using LongPointer = int64;
	
	using ULongPointer = uint64;
	
	#elif defined(WHALE_COMPILER_BIT_32)
	
	using IntPointer = Int;
	
	using UIntPointer = UInt;
	
	using LongPointer = Long;
	
	using ULongPointer = ULong;
	
	#endif
	
	using SizeT = uint64;
	
	using Char = CharW;

#ifdef WHALE_UNICODE
	using CharT = CharW;
#else
	using CharT = CharA;
#endif
	
	// 致命消息
	WHALE_API void Assert(const CharA *message, const CharA *file, uint64 line, const CharA *function);
	
	// 致命消息
	WHALE_API void Assert(const CharW *message, const CharW *file, uint64 line, const CharW *function);
	
	
} // Whale
