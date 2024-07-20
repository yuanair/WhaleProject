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
		
		WClass(StringA name, const Bool isClass, const Bool isFinal)
			: name(Move(name)), isClass(isClass), isFinal(isFinal) {}
	
	public:
		
		const StringA name;
		
		const Bool isClass; // true - class/false - struct
		
		const Bool isFinal;
		
	};
	
	///
	/// 枚举数据类型
	class WHALE_API WEnum final : public WType
	{
	public:
		
		explicit WEnum(StringA name)
			: name(Move(name)) {}
	
	public:
		
		const StringA name;
		
	};
	
	///
	/// 联合体数据类型
	class WHALE_API WUnion final : public WType
	{
	public:
		
		explicit WUnion(StringA name)
			: name(Move(name)) {}
	
	public:
		
		const StringA name;
		
	};
	
} // Whale
