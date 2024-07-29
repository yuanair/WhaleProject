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
#define WHALE_ASSERT(expression, message) ((!!(expression)) || (::Whale::FatalMessage(message, WHALE_WIDE(__FILE__), __LINE__, WHALE_WIDE(__FUNCSIG__)), 0))
#else
#define WHALE_ASSERT(expression, message) ((void)0)
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
	
	
	
	// 致命消息
	WHALE_API void FatalMessage(const CharW *message, const CharW *file, uint64 line, const CharW *function);
	
	
} // Whale
