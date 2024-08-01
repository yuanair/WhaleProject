//
// Created by admin on 2024/6/16.
//

#pragma once

#include "TypeDef.hpp"
#include "Memory.hpp"

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
		
		FCloneable() = default;
		
		virtual ~FCloneable() = default;
	
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
	
	template<class Base, class Derived>
	class WHALE_API FNeedCloneable
	{
	public:
		
		FNeedCloneable() = default;
		
		virtual ~FNeedCloneable() = default;
	
	public:
		
		///
		/// 克隆对象
		/// \return 克隆体
		[[nodiscard]]
		inline virtual TFUniquePtr<Base> Clone() const = 0;
		
	};
	
	// Object类
	class WHALE_API WObject : public FCloneable<WObject, WObject>
	{
	public:
		
		WObject();
		
		WObject(const WObject &other) = default;
		
		~WObject() override;
	
	public:
		
		WObject &operator=(const WObject &other) = default;
		
	};
	
	///
	/// 可克隆的
	/// \tparam Derived 派生类
	template<class Derived>
	using FObjectCloneable = FCloneable<WObject, Derived>;
	
	template<class Derived>
	using FObjectNeedCloneable = FNeedCloneable<WObject, Derived>;
	
	
} // Whale
