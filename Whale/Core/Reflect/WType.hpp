//
// Created by admin on 2024/7/15.
//

#pragma once

#include "Whale/Core/Object/WObject.hpp"
#include "Whale/Core/Container/FTString.hpp"

namespace Whale
{
	
	///
	/// 数据类型
	class WType : public WObject
	{
	public:
	
	
	};
	
	///
	/// 类/结构体数据类型
	class WClass final : public WType
	{
	public:
		
		WClass(FTStringA name, const Bool isClass, const Bool isFinal)
			: name(Move(name)), isClass(isClass), isFinal(isFinal) {}
	
	public:
		
		const FTStringA name;
		
		const Bool isClass; // true - class/false - struct
		
		const Bool isFinal;
		
	};
	
	///
	/// 枚举数据类型
	class WEnum final : public WType
	{
	public:
		
		explicit WEnum(FTStringA name)
			: name(Move(name)) {}
	
	public:
		
		const FTStringA name;
		
	};
	
	///
	/// 联合体数据类型
	class WUnion final : public WType
	{
	public:
		
		explicit WUnion(FTStringA name)
			: name(Move(name)) {}
	
	public:
		
		const FTStringA name;
		
	};
	
} // Whale
