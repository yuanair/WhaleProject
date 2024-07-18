//
// Created by admin on 2024/7/15.
//

#pragma once

#include "Whale/Core/Tool/HTypeDef.hpp"
#include "Whale/Core/Tool/HCRT.hpp"
#include "Whale/Core/Container/HMemory.hpp"
#include "WType.hpp"

#include <vector>
#include <typeinfo>

namespace Whale
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
		
		static std::vector<WClass> classes;
		
		static std::vector<WEnum> enums;
		
		static std::vector<WUnion> unions;
		
	};
	
	template<class T>
	WType &FReflect::Register()
	{
		if constexpr (IsClassValue<T>)
		{
			return classes.emplace_back(typeid(T).name(), IsClassValue<T>, IsFinalValue<T>);
		}
		else if constexpr (IsEnumValue<T>)
		{
			return enums.emplace_back(typeid(T).name());
		}
		else if constexpr (IsUnionValue<T>)
		{
			return unions.emplace_back(typeid(T).name());
		}
		else
		{
			static_assert(true || "T can not Register");
		}
	}
	
	
} // Whale
