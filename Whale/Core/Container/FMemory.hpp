//
// Created by admin on 2024/7/17.
//

#pragma once

#include "Whale/Core/Tool/FTypeDef.hpp"
#include "Whale/Core/Tool/FIntrinsics.hpp"
#include "Whale/Core/FException/FException.hpp"

namespace Whale
{
	
	///
	/// 独有指针
	template<class ElemT>
	class WHALE_API FTUniquePtr;
	
	///
	/// 共享指针
	template<class ElemT>
	class WHALE_API FTSharedPtr;
	
	///
	/// 观察指针
	template<class ElemT>
	class WHALE_API FTWeakPtr;
	
	class FBadWeakPtrException : public FException
	{
	public:
		FBadWeakPtrException() noexcept = default;
		
		[[nodiscard]] const Char *what() const noexcept override { return "FBadWeakPtrException"; }
	};
	
	template<class ElemT>
	class WHALE_API FTUniquePtr
	{
		
		template<class> friend
		class FTUniquePtr;
	
	public:
		
		FTUniquePtr(const FTUniquePtr &other) = delete;
		
		FTUniquePtr &operator=(const FTUniquePtr &other) noexcept = delete;
	
	public:
		
		constexpr FTUniquePtr() noexcept: ptr(nullptr) {}
		
		constexpr FTUniquePtr(NullPtrT) noexcept: ptr(nullptr) {} // NOLINT(*-explicit-constructor)
		
		explicit FTUniquePtr(ElemT *ptr) noexcept: ptr(ptr) {}
		
		FTUniquePtr(FTUniquePtr &&other) noexcept: ptr(other.Release()) {}
		
		template<typename T>
		FTUniquePtr(const FTUniquePtr<T> &other) noexcept: ptr(other.ptr) {} // NOLINT(*-explicit-constructor)
		
		template<typename T>
		FTUniquePtr(FTUniquePtr<T> &&other) noexcept: ptr(other.Release()) {} // NOLINT(*-explicit-constructor)
		
		~FTUniquePtr() noexcept { Reset(); }
	
	public:
		
		FTUniquePtr &operator=(FTUniquePtr &&other) noexcept
		{
			Reset(other.Release());
			return *this;
		}
		
		ElemT *operator->() const noexcept { return this->ptr; }
		
		ElemT &operator*() const noexcept { return *this->ptr; }
		
		ElemT &operator[](SizeT index) const noexcept { return this->ptr[index]; }
		
		explicit operator Bool() { return static_cast<Bool>(this->ptr); }
	
	public:
		
		///
		/// 不释放空间，重置指针
		/// \return 指针
		ElemT *Release() noexcept
		{
			ElemT *old = this->ptr;
			this->ptr = nullptr;
			return old;
		}
		
		///
		/// 重置
		/// \param ptrArg 指针
		void Reset(ElemT *ptrArg = nullptr) noexcept
		{
			if (this->ptr != nullptr) delete this->ptr;
			this->ptr = ptrArg;
		}
		
		///
		/// 交换数据
		/// \param other
		void Swap(FTUniquePtr &other) noexcept { Whale::Swap(this->ptr, other.ptr); }
	
	public:
		
		///
		/// \return 指针
		[[nodiscard]]
		ElemT *GetPtr() const noexcept { return this->ptr; }
	
	private:
		
		ElemT *ptr;
		
	};
	
	
	class WHALE_API _FUseCountBase // NOLINT(*-reserved-identifier)
	{
	protected:
		
		constexpr _FUseCountBase() noexcept
			: uses(1), weaks(1) {}
	
	public:
		
		_FUseCountBase(const _FUseCountBase &) noexcept = delete;
		
		virtual ~_FUseCountBase() noexcept = default;
	
	public:
		
		_FUseCountBase &operator=(const _FUseCountBase &) noexcept = delete;
	
	public:
		
		bool IncrementUseNoZero() noexcept
		{
			if (this->uses == 0) return false;
			++this->uses;
			return true;
		}
		
		void IncrementUse() noexcept
		{
			++this->uses;
		}
		
		void IncrementWeak() noexcept
		{
			++this->weaks;
		}
		
		void DecrementUse() noexcept
		{
			if (--this->uses == 0)
			{
				Destroy();
				DecrementWeak();
			}
		}
		
		void DecrementWeak() noexcept
		{
			if (--this->weaks == 0)
			{
				DeleteThis();
			}
		}
	
	public:
		
		[[nodiscard]] AtomicCounterT GetUses() const noexcept { return this->uses; }
		
		[[nodiscard]] AtomicCounterT GetWeaks() const noexcept { return this->weaks; }
	
	private:
		
		virtual void Destroy() noexcept = 0;
		
		virtual void DeleteThis() noexcept = 0;
	
	private:
		
		std::atomic<AtomicCounterT> uses;
		
		std::atomic<AtomicCounterT> weaks;
		
	};
	
	template<class ElemT>
	class WHALE_API _FTUseCount : public _FUseCountBase // NOLINT(*-reserved-identifier)
	{
	public:
		
		explicit _FTUseCount(ElemT *ptrArg) : _FUseCountBase(), ptr(ptrArg) {}
	
	private:
		
		void Destroy() noexcept override
		{
			delete this->ptr;
		}
		
		void DeleteThis() noexcept override
		{
			delete this;
		}
	
	private:
		
		ElemT *ptr;
		
	};
	
	///
	/// 指针基类
	template<class ElemT>
	class WHALE_API _FTPtrBase // NOLINT(*-reserved-identifier)
	{
	public:
		
		template<class> friend
		class _FTPtrBase; // NOLINT(*-reserved-identifier)
	
	protected:
		
		constexpr _FTPtrBase() noexcept
			: ptr(nullptr), useCount(nullptr) {}
		
		~_FTPtrBase() = default;
	
	public:
		
		///
		/// \return 获取使用引用计数
		[[nodiscard]] AtomicCounterT GetUseCount() const noexcept
		{
			return this->useCount ? this->useCount->GetUses() : 0;
		}
		
		///
		/// \return 获取查看引用计数
		[[nodiscard]] AtomicCounterT GetWeakCount() const noexcept
		{
			return this->useCount ? this->useCount->GetWeaks() : 0;
		}
	
	protected:
		
		template<class T>
		void MoveConstructFrom(_FTPtrBase<T> &&other)
		{
			this->ptr = other.ptr;
			this->useCount = other.useCount;
			other.ptr = nullptr;
			other.useCount = nullptr;
		}
		
		template<class T>
		void CopyConstructFrom(const _FTPtrBase<T> &other)
		{
			other.IncrementUse();
			this->ptr = other.ptr;
			this->useCount = other.useCount;
		}
		
		template<class T>
		bool ConstructFromWeak(const FTWeakPtr<T> &other) noexcept
		{
			if (other.useCount && other.useCount->IncrementUseNoZero())
			{
				this->ptr = other.ptr;
				this->useCount = other.useCount;
				return true;
			}
			
			return false;
		}
		
		template<class T>
		void WeaklyConstructFrom(const _FTPtrBase<T> &other) noexcept
		{
			if (other.useCount)
			{
				this->ptr = other.ptr;
				this->useCount = other.useCount;
				this->useCount->IncrementWeak();
			}
			else
			{
				WHALE_ASSERT(!this->ptr && !this->useCount);
			}
		}
		
		void IncrementUse() const noexcept { if (this->useCount) this->useCount->IncrementUse(); }
		
		void IncrementWeak() const noexcept { if (this->useCount) this->useCount->IncrementWeak(); }
		
		void DecrementUse() noexcept { if (this->useCount) this->useCount->DecrementUse(); }
		
		void DecrementWeak() noexcept { if (this->useCount) this->useCount->DecrementWeak(); }
		
		void BaseSwap(_FTPtrBase &other) noexcept
		{
			Whale::Swap(this->ptr, other.ptr);
			Whale::Swap(this->useCount, other.useCount);
		}
	
	protected:
		
		[[nodiscard]] ElemT *GetPtr() const noexcept { return this->ptr; }
	
	protected:
		
		ElemT *ptr;
		
		_FUseCountBase *useCount;
		
	};
	
	template<class ElemT>
	class WHALE_API FTSharedPtr : public _FTPtrBase<ElemT>
	{
	public:
		
		template<class> friend
		class FTSharedPtr;
		
		template<class> friend
		class FTWeakPtr;
	
	public:
		
		constexpr FTSharedPtr() noexcept = default;
		
		constexpr FTSharedPtr(NullPtrT) noexcept {}; // NOLINT(*-explicit-constructor)
		
		explicit FTSharedPtr(ElemT *ptr) { EnableShared(ptr); }
		
		FTSharedPtr(const FTSharedPtr &other) { this->CopyConstructFrom(other); }
		
		template<typename T>
		FTSharedPtr(const FTSharedPtr<T> &other) noexcept // NOLINT(*-explicit-constructor)
		{
			this->CopyConstructFrom(other);
		}
		
		FTSharedPtr(FTSharedPtr &&other) noexcept { this->MoveConstructFrom(Whale::Move(other)); }
		
		template<typename T>
		FTSharedPtr(FTSharedPtr<T> &&other) noexcept // NOLINT(*-explicit-constructor)
		{
			this->MoveConstructFrom(Whale::Move(other));
		}
		
		template<typename T>
		explicit FTSharedPtr(const FTWeakPtr<T> &other)
		{
			if (!this->ConstructFromWeak(Whale::Move(other)))
			{
				throw FBadWeakPtrException();
			}
		}
		
		template<typename T>
		FTSharedPtr(FTUniquePtr<T> &&other) // NOLINT(*-explicit-constructor)
		{
			auto *ptr = other.GetPtr();
			if (ptr)
			{
				EnableShared(ptr);
				other.Release();
			}
		}
		
		~FTSharedPtr() noexcept { this->DecrementUse(); }
	
	public:
		
		FTSharedPtr &operator=(const FTSharedPtr &other) noexcept
		{
			FTSharedPtr(other).Swap(*this);
			return *this;
		}
		
		template<typename T>
		FTSharedPtr &operator=(const FTSharedPtr<T> &other) noexcept
		{
			FTSharedPtr(other).Swap(*this);
			return *this;
		}
		
		FTSharedPtr &operator=(FTSharedPtr &&other) noexcept
		{
			FTSharedPtr(Whale::Move(other)).Swap(*this);
			return *this;
		}
		
		template<typename T>
		FTSharedPtr &operator=(FTSharedPtr<T> &&other) noexcept
		{
			FTSharedPtr(Whale::Move(other)).Swap(*this);
			return *this;
		}
		
		template<typename T>
		FTSharedPtr &operator=(FTUniquePtr<T> &&other) noexcept
		{
			FTSharedPtr(Whale::Move(other)).Swap(*this);
			return *this;
		}
		
		ElemT *operator->() const noexcept { return this->ptr; }
		
		ElemT &operator*() const noexcept { return *this->ptr; }
		
		ElemT &operator[](SizeT index) const noexcept { return this->ptr[index]; }
		
		explicit operator Bool() { return this->ptr != nullptr; }
	
	public:
		
		///
		/// 重置
		void Reset() noexcept { FTSharedPtr().Swap(*this); }
		
		///
		/// 重置
		/// \param ptrArg 指针
		void Reset(ElemT *ptrArg) noexcept { FTSharedPtr(ptrArg).Swap(*this); }
		
		///
		/// 交换数据
		/// \param other
		void Swap(FTSharedPtr &other) noexcept { this->BaseSwap(other); }
	
	private:
		
		template<class T>
		void EnableShared(T *ptrArg) noexcept;
		
	};
	
	template<class ElemT>
	class WHALE_API FTWeakPtr : public _FTPtrBase<ElemT>
	{
	public:
		
		template<class> friend
		class FTWeakPtr;
	
	public:
		
		constexpr FTWeakPtr() noexcept = default;
		
		FTWeakPtr(const FTWeakPtr &other) noexcept
		{
			this->WeaklyConstructFrom(other);
		}
		
		template<class T>
		FTWeakPtr(const FTSharedPtr<T> &other) noexcept // NOLINT(*-explicit-constructor)
		{
			this->WeaklyConstructFrom(other);
		}
		
		template<class T>
		FTWeakPtr(const FTWeakPtr<T> &other) noexcept // NOLINT(*-explicit-constructor)
		{
			this->WeaklyConstructFrom(other);
		}
		
		FTWeakPtr(FTWeakPtr &&other) noexcept
		{
			this->MoveConstructFrom(Whale::Move(other));
		}
		
		template<class T>
		FTWeakPtr(FTWeakPtr<T> &&other) noexcept // NOLINT(*-explicit-constructor)
		{
			this->MoveConstructFrom(Whale::Move(other));
		}
		
		~FTWeakPtr() noexcept { this->DecrementWeak(); }
	
	public:
		
		FTWeakPtr &operator=(const FTWeakPtr &other) noexcept
		{
			FTWeakPtr(other).Swap(*this);
			return *this;
		}
		
		template<typename T>
		FTWeakPtr &operator=(const FTWeakPtr<T> &other) noexcept
		{
			FTWeakPtr(other).Swap(*this);
			return *this;
		}
		
		FTWeakPtr &operator=(FTWeakPtr &&other) noexcept
		{
			FTWeakPtr(Whale::Move(other)).Swap(*this);
			return *this;
		}
		
		template<typename T>
		FTWeakPtr &operator=(FTWeakPtr<T> &&other) noexcept
		{
			FTWeakPtr(Whale::Move(other)).Swap(*this);
			return *this;
		}
		
		template<typename T>
		FTWeakPtr &operator=(FTSharedPtr<T> &&other) noexcept
		{
			FTWeakPtr(Whale::Move(other)).Swap(*this);
			return *this;
		}
	
	public:
		
		///
		/// 重置
		void Reset() noexcept { FTWeakPtr{}.Swap(*this); }
		
		///
		/// 交换数据
		/// \param other
		void Swap(FTWeakPtr &other) noexcept { this->BaseSwap(other); }
		
		///
		/// \return 是否过期了
		[[nodiscard]]
		Bool Expired() const noexcept
		{
			return this->GetUseCount() == 0;
		}
		
		///
		/// \return 锁住资源
		[[nodiscard]]
		FTSharedPtr<ElemT> Lock() const noexcept
		{
			FTSharedPtr<ElemT> result;
			(void) result.ConstructFromWeak(*this);
			return result;
		}
		
	};
	
	
} // Whale

#include "FMemory.inl"
