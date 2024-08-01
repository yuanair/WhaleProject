//
// Created by admin on 2024/7/23.
//

#pragma once

#include "../Utility.hpp"
#include "InitList.hpp"

namespace Whale::Container
{
	
	///
	/// 对
	/// \tparam T1
	/// \tparam T2
	template<class T1, class T2>
	class TFPair
	{
	public:
		
		constexpr explicit TFPair() : first(), second() {}
		
		constexpr explicit TFPair(const T1 &v1, const T2 &v2) : first(v1), second(v2) {}
		
		template<typename U1, typename U2>
		constexpr explicit TFPair(U1 &&v1, U2 &&v2) : first(Whale::Forward<U1>(v1)), second(Whale::Forward<U2>(v2)) {}
		
		template<typename U1, typename U2>
		constexpr explicit TFPair(const TFPair<U1, U2> &other): first(other.first), second(other.second) {}
		
		template<typename U1, typename U2>
		constexpr explicit TFPair(TFPair<U1, U2> &&other) noexcept: first(Whale::Forward<U1>(other.first)),
		                                                            second(Whale::Forward<U2>(other.second)) {}
		
		TFPair &operator=(const volatile TFPair &) = delete;
		
		TFPair(const TFPair &) = default;
		
		TFPair(TFPair &&) = default;
	
	public:
		
		constexpr TFPair &operator=(const TFPair &other)
		{
			first  = other.first;
			second = other.second;
			return *this;
		}
		
		constexpr TFPair &operator=(TFPair &&other) noexcept
		{
			first  = Whale::Forward<T1>(other.first);
			second = Whale::Forward<T2>(other.second);
			return *this;
		}
		
		template<typename U1, typename U2>
		constexpr TFPair &operator=(const TFPair<U1, U2> &other)
		{
			first  = other.first;
			second = other.second;
			return *this;
		}
		
		template<typename U1, typename U2>
		constexpr TFPair &operator=(TFPair<U1, U2> &&other) noexcept
		{
			first  = Whale::Forward<U1>(other.first);
			second = Whale::Forward<U2>(other.second);
			return *this;
		}
	
	public:
		
		///
		/// 交换数据
		/// \param other
		void Swap(TFPair &other) noexcept
		{
			if (this == &other) return;
			using Whale::Swap;
			Swap(first, other.first);
			Swap(second, other.second);
		}
	
	public:
		
		T1 first;
		
		T2 second;
		
	};
	
} // Whale
