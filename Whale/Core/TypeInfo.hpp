//
// Created by admin on 2024/7/22.
//

#pragma once

#include "TypeDef.hpp"
#include <typeinfo>

namespace Whale
{
	
	
	template<typename T>
	const std::type_info &GetTypeInfo() noexcept
	{
		return typeid(T);
	}
	
	template<typename Ptr>
	const std::type_info &GetTypeInfo(Ptr ptr) noexcept
	{
		return typeid(*ptr);
	}
	
	///
	/// \tparam T
	/// \tparam Ptr
	/// \param ptr
	/// \return 指针指向的对象是否等于T类型
	template<typename T, typename Ptr>
	Bool Is(Ptr ptr) noexcept
	{
		return GetTypeInfo<T>() == GetTypeInfo(ptr);
	}
	
	///
	/// \tparam Base
	/// \tparam T
	/// \param ptr
	/// \return 动态转换为Base*
	template<typename Base, typename T>
	Base *Cast(T *ptr) noexcept
	{
		return dynamic_cast<Base *>(ptr);
	}
	
} // Whale
