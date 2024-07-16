//
// Created by admin on 2024/7/15.
//

#pragma once

#include "Whale/Core/Tool/FTypeDef.hpp"
#include "WType.hpp"
#include "Whale/Core/Tool/FCRT.hpp"

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
		inline static const WType *Register();
	
	public:
		
		static const std::vector<const WClass *> &GetClasses()
		{
			return classes;
		}
		
		static const std::vector<const WEnum *> &GetEnums()
		{
			return enums;
		}
		
		static const std::vector<const WUnion *> &GetUnions()
		{
			return unions;
		}
	
	private:
		
		static std::vector<const WClass *> classes;
		
		static std::vector<const WEnum *> enums;
		
		static std::vector<const WUnion *> unions;
		
	};
	
	template<class T>
	const WType *FReflect::Register()
	{
		if constexpr (IsClassValue<T>)
		{
			const WClass *type = WHALE_DBG_NEW WClass(typeid(T).name(), IsClassValue<T>, IsFinalValue<T>);
			classes.push_back(type);
			return type;
		}
		else if constexpr (IsEnumValue<T>)
		{
			const WEnum *type = WHALE_DBG_NEW WEnum(typeid(T).name());
			enums.push_back(type);
			return type;
		}
		else if constexpr (IsUnionValue<T>)
		{
			const WUnion *type = WHALE_DBG_NEW WUnion(typeid(T).name());
			unions.push_back(type);
			return type;
		}
		else
		{
			static_assert(true || "T can not Register");
		}
	}
	
	
} // Whale
