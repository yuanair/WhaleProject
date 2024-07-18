//
// Created by admin on 2024/6/16.
//

#pragma once

#include "Whale/Core/Tool/HTypeDef.hpp"
#include "Whale/Core/Container/HMemory.hpp"

namespace Whale
{
	
	///
	/// 可克隆的
	/// \tparam Base 基类
	/// \tparam Derived 派生类
	template<class Base, class Derived>
	class WHALE_API FCloneable
	{
	public:
		
		///
		/// 克隆对象
		/// \return 克隆体
		[[nodiscard]]
		inline virtual TFUniquePtr<Base> Clone() const
		{
			return MakeUnique<Derived>(static_cast<Derived const &>(*this));
		}
		
	};
	
	// Object类
	class WHALE_API WObject : public FCloneable<WObject, WObject>
	{
	public:
		
		WObject();
		
		virtual ~WObject();
		
	};
	
	///
	/// 可克隆的
	/// \tparam Derived 派生类
	template<class Derived>
	using FObjectCloneable = FCloneable<WObject, Derived>;
	
	
} // Whale
