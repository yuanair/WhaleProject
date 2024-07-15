//
// Created by admin on 2024/6/16.
//

#pragma once

#include "FTypeDef.hpp"
#include <string>

namespace Whale
{
	// Object类
	class WHALE_API WObject
	{
	public:
		
		WObject();
		
		WObject(const WObject &) = delete;
		
		virtual ~WObject();
	
	public:
		
		WObject &operator=(const WObject &) = delete;
	
	public:
		
		///
		/// \param other
		/// \return 是否相等
		[[nodiscard]]
		virtual bool Equals(const WObject &other) const;
		
		///
		/// \return 克隆体
		[[nodiscard]]
		virtual WObject *Clone() const;
		
		///
		/// \return 字符串
		[[nodiscard]]
		virtual std::string ToString() const;
		
	};
	
} // Whale
