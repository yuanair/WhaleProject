//
// Created by admin on 2024/7/11.
//

#pragma once

#include "Whale/Core/FTypeDef.hpp"

namespace Whale
{
	///
	/// 未定义数据
	template<class T>
	class WHALE_API FUndefinedData
	{
	public:
		
		FUndefinedData()
			: ptr(nullptr)
		{
		
		}
		
		FUndefinedData(const FUndefinedData &other) = delete;
		
		FUndefinedData(FUndefinedData &&other) noexcept
			: ptr(nullptr)
		{
			Swap(other);
		}
		
		~FUndefinedData()
		{
			delete this->ptr;
			this->ptr = nullptr;
		}
	
	public:
		
		FUndefinedData &operator=(FUndefinedData other)
		{
			Swap(other);
			return *this;
		}
		
		T &operator*() { return *this->ptr; }
		
		const T &operator*() const { return *this->ptr; }
		
		T *operator->() const { return this->ptr; }
		
		T *Get() const { return this->ptr; }
	
	public:
		
		///
		/// 创建
		/// \tparam Args
		/// \param args
		template<class... Args>
		void New(const Args &... args)
		{
			this->ptr = new T{args...};
		}
		
		///
		/// 交换数据
		/// \param other
		void Swap(FUndefinedData &other)
		{
			Whale::Swap(this->ptr, other.ptr);
		}
	
	private:
		
		T *ptr;
		
	};
	
} // Whale
