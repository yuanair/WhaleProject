//
// Created by admin on 2024/7/16.
//

#pragma once

#include "Whale/Core/Tool/FTypeDef.hpp"
#include "Whale/Core/Tool/FCRT.hpp"

namespace Whale
{
	///
	/// 指针
	template<class ElemT>
	class WHALE_API FTUniquePtr
	{
	public:
		
		template<class> friend
		class FTUniquePtr;
	
	public:
		
		inline FTUniquePtr();
		
		inline FTUniquePtr(NullPtrT); // NOLINT(*-explicit-constructor)
		
		inline explicit FTUniquePtr(ElemT *ptr);
		
		inline FTUniquePtr(const FTUniquePtr &other) = delete;
		
		inline FTUniquePtr(FTUniquePtr &&other) noexcept;
		
		template<typename T>
		inline FTUniquePtr(const FTUniquePtr<T> &other) noexcept; // NOLINT(*-explicit-constructor)
		
		template<typename T>
		inline FTUniquePtr(FTUniquePtr<T> &&other) noexcept; // NOLINT(*-explicit-constructor)
		
		inline ~FTUniquePtr() noexcept;
	
	public:
		
		inline FTUniquePtr &operator=(const FTUniquePtr &other) noexcept = delete;
		
		inline FTUniquePtr &operator=(FTUniquePtr &&other) noexcept;
		
		inline ElemT *operator->() const noexcept { return this->ptr; }
		
		inline ElemT &operator*() const noexcept { return *this->ptr; }
		
		inline ElemT &operator[](SizeT index) const noexcept { return this->ptr[index]; }
		
		inline explicit operator Bool() { return static_cast<Bool>(this->ptr); }
	
	public:
		
		///
		/// 不释放空间，重置指针
		/// \return 指针
		inline ElemT *Release() noexcept;
		
		///
		/// 重置
		/// \param ptrArg 指针
		inline void Reset(ElemT *ptrArg = nullptr) noexcept;
		
		///
		/// 交换数据
		/// \param other
		inline void Swap(FTUniquePtr &other) noexcept;
	
	public:
		
		///
		/// \return 指针
		[[nodiscard]]
		inline ElemT *GetPtr() const noexcept { return this->ptr; }
	
	private:
		
		ElemT *ptr;
		
	};
	
	///
	/// \tparam ElemT
	/// \tparam Args
	/// \param args
	/// \return
	template<class ElemT, class... Args>
	inline FTUniquePtr<ElemT> MakeUnique(Args &&... args)
	{
		return FTUniquePtr<ElemT>(WHALE_DBG_NEW ElemT(Forward<Args>(args)...));
	}
	
	template<class ElemT>
	FTUniquePtr<ElemT>::FTUniquePtr()
		: ptr(nullptr)
	{
	
	}
	
	template<class ElemT>
	FTUniquePtr<ElemT>::FTUniquePtr(NullPtrT)
		: ptr(nullptr)
	{
	
	}
	
	template<class ElemT>
	FTUniquePtr<ElemT>::FTUniquePtr(ElemT *ptr)
		: ptr(ptr)
	{
	
	}
	
	template<class ElemT>
	FTUniquePtr<ElemT>::FTUniquePtr(FTUniquePtr &&other) noexcept
		: ptr(other.Release())
	{
	
	}
	
	template<class ElemT>
	template<typename T>
	FTUniquePtr<ElemT>::FTUniquePtr(const FTUniquePtr<T> &other) noexcept
		: ptr(other.ptr)
	{
	
	}
	
	template<class ElemT>
	template<typename T>
	FTUniquePtr<ElemT>::FTUniquePtr(FTUniquePtr<T> &&other) noexcept
		: ptr(other.Release())
	{
	
	}
	
	template<class ElemT>
	FTUniquePtr<ElemT>::~FTUniquePtr() noexcept
	{
		Reset();
	}
	
	template<class ElemT>
	FTUniquePtr<ElemT> &FTUniquePtr<ElemT>::operator=(FTUniquePtr &&other) noexcept
	{
		Reset(other.Release());
		return *this;
	}
	
	template<class ElemT>
	ElemT *FTUniquePtr<ElemT>::Release() noexcept
	{
		ElemT *old = this->ptr;
		this->ptr = nullptr;
		return old;
	}
	
	template<class ElemT>
	void FTUniquePtr<ElemT>::Reset(ElemT *ptrArg) noexcept
	{
		if (this->ptr != nullptr) delete this->ptr;
		this->ptr = ptrArg;
	}
	
	template<class ElemT>
	void FTUniquePtr<ElemT>::Swap(FTUniquePtr &other) noexcept
	{
		Whale::Swap(this->ptr, other.ptr);
	}
	
} // Whale
