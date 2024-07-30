//
// Created by admin on 2024/7/15.
//

#pragma once

#include "Whale/Core/WObject.hpp"
#include "Whale/Core/Container/TFString.hpp"

namespace Whale::Reflect
{
	
	///
	/// 数据类型
	class WHALE_API WType : public WObject
	{
	public:
	
	
	};
	
	///
	/// 类/结构体数据类型
	class WHALE_API WClass final : public WType
	{
	public:
		
		WClass() : name(""), isClass(false), isFinal(false) {}
		
		WClass(StringA name, const Bool isClass, const Bool isFinal)
			: name(Move(name)), isClass(isClass), isFinal(isFinal) {}
	
	public:
		
		StringA name;
		
		Bool isClass; // true - class/false - struct
		
		Bool isFinal;
		
	};
	
	///
	/// 枚举数据类型
	class WHALE_API WEnum final : public WType
	{
	public:
		
		WEnum() : name("") {}
		
		explicit WEnum(StringA name)
			: name(Move(name)) {}
	
	public:
		
		StringA name;
		
	};
	
	///
	/// 联合体数据类型
	class WHALE_API WUnion final : public WType
	{
	public:
		
		WUnion() : name("") {}
		
		explicit WUnion(StringA name)
			: name(Move(name)) {}
	
	public:
		
		StringA name;
		
	};
	
} // Whale
