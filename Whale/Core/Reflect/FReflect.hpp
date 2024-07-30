//
// Created by admin on 2024/7/15.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"
#include "Whale/Core/CRT.hpp"
#include "Whale/Core/Memory.hpp"
#include "WType.hpp"

#include <vector>
#include <typeinfo>

namespace Whale::Reflect
{
	
	///
	/// 反射
	class WHALE_API FReflect
	{
	public:
		
		template<class T>
		inline static WType &Register();
	
	public:
		
		static const auto &GetClasses()
		{
			return classes;
		}
		
		static const auto &GetEnums()
		{
			return enums;
		}
		
		static const auto &GetUnions()
		{
			return unions;
		}
	
	private:
		
		static Container::TFArray<WClass> classes;
		
		static Container::TFArray<WEnum> enums;
		
		static Container::TFArray<WUnion> unions;
		
	};
	
	template<class T>
	WType &FReflect::Register()
	{
		if constexpr (std::is_class_v<T>)
		{
			return classes.Emplace(typeid(T).name(), std::is_class_v<T>, std::is_final_v<T>);
		}
		else if constexpr (std::is_enum_v<T>)
		{
			return enums.Emplace(typeid(T).name());
		}
		else if constexpr (std::is_union_v<T>)
		{
			return unions.Emplace(typeid(T).name());
		}
		else
		{
			static_assert(true || "T can not Register");
		}
	}
	
	
} // Whale
