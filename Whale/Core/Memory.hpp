//
// Created by admin on 2024/7/17.
//

#pragma once

#include "TypeDef.hpp"
#include "FIntrinsics.hpp"
#include "Exception.hpp"
#include "FDebug.hpp"

namespace Whale
{
	
	///
	/// 独有指针
	template<class ElemT>
	class WHALE_API TFUniquePtr;
	
	///
	/// 共享指针
	template<class ElemT>
	class WHALE_API TFSharedPtr;
	
	///
	/// 观察指针
	template<class ElemT>
	class WHALE_API TFWeakPtr;
	
	class FBadWeakPtrException : public FException
	{
	public:
		FBadWeakPtrException() noexcept = default;
		
		[[nodiscard]] const CharA *what() const noexcept override { return "FBadWeakPtrException"; }
	};
	
	template<class ElemT>
	class WHALE_API TFUniquePtr
	{
		
		template<class> friend
		class TFUniquePtr;
	
	public:
		
		TFUniquePtr(const TFUniquePtr &other) = delete;
		
		TFUniquePtr &operator=(const TFUniquePtr &other) noexcept = delete;
	
	public:
		
		constexpr TFUniquePtr() noexcept: ptr(nullptr) {}
		
		constexpr TFUniquePtr(NullPtrT) noexcept: ptr(nullptr) {} // NOLINT(*-explicit-constructor)
		
		explicit TFUniquePtr(ElemT *ptr) noexcept: ptr(ptr) {}
		
		TFUniquePtr(TFUniquePtr &&other) noexcept: ptr(other.Release()) {}
		
		template<typename T>
		TFUniquePtr(const TFUniquePtr<T> &other) noexcept: ptr(other.ptr) {} // NOLINT(*-explicit-constructor)
		
		template<typename T>
		TFUniquePtr(TFUniquePtr<T> &&other) noexcept: ptr(other.Release()) {} // NOLINT(*-explicit-constructor)
		
		~TFUniquePtr() noexcept { Reset(); }
	
	public:
		
		TFUniquePtr &operator=(TFUniquePtr &&other) noexcept
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
		void Swap(TFUniquePtr &other) noexcept { Whale::Swap(this->ptr, other.ptr); }
	
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
	class WHALE_API _TFUseCount : public _FUseCountBase // NOLINT(*-reserved-identifier)
	{
	public:
		
		explicit _TFUseCount(ElemT *ptrArg) : _FUseCountBase(), ptr(ptrArg) {}
	
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
	class WHALE_API _TFPtrBase // NOLINT(*-reserved-identifier)
	{
	public:
		
		template<class> friend
		class _TFPtrBase; // NOLINT(*-reserved-identifier)
	
	protected:
		
		constexpr _TFPtrBase() noexcept
			: ptr(nullptr), useCount(nullptr) {}
		
		~_TFPtrBase() = default;
	
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
		void MoveConstructFrom(_TFPtrBase<T> &&other)
		{
			this->ptr = other.ptr;
			this->useCount = other.useCount;
			other.ptr = nullptr;
			other.useCount = nullptr;
		}
		
		template<class T>
		void CopyConstructFrom(const _TFPtrBase<T> &other)
		{
			other.IncrementUse();
			this->ptr = other.ptr;
			this->useCount = other.useCount;
		}
		
		template<class T>
		bool ConstructFromWeak(const TFWeakPtr<T> &other) noexcept
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
		void WeaklyConstructFrom(const _TFPtrBase<T> &other) noexcept
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
		
		void BaseSwap(_TFPtrBase &other) noexcept
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
	class WHALE_API TFSharedPtr : public _TFPtrBase<ElemT>
	{
	public:
		
		template<class> friend
		class TFSharedPtr;
		
		template<class> friend
		class TFWeakPtr;
	
	public:
		
		constexpr TFSharedPtr() noexcept = default;
		
		constexpr TFSharedPtr(NullPtrT) noexcept {}; // NOLINT(*-explicit-constructor)
		
		explicit TFSharedPtr(ElemT *ptr) { EnableShared(ptr); }
		
		TFSharedPtr(const TFSharedPtr &other) { this->CopyConstructFrom(other); }
		
		template<typename T>
		TFSharedPtr(const TFSharedPtr<T> &other) noexcept // NOLINT(*-explicit-constructor)
		{
			this->CopyConstructFrom(other);
		}
		
		TFSharedPtr(TFSharedPtr &&other) noexcept { this->MoveConstructFrom(Whale::Move(other)); }
		
		template<typename T>
		TFSharedPtr(TFSharedPtr<T> &&other) noexcept // NOLINT(*-explicit-constructor)
		{
			this->MoveConstructFrom(Whale::Move(other));
		}
		
		template<typename T>
		explicit TFSharedPtr(const TFWeakPtr<T> &other)
		{
			if (!this->ConstructFromWeak(Whale::Move(other)))
			{
				FDebug::LogError(WhaleTagA, FBadWeakPtrException());
				return;
			}
		}
		
		template<typename T>
		TFSharedPtr(TFUniquePtr<T> &&other) // NOLINT(*-explicit-constructor)
		{
			auto *ptr = other.GetPtr();
			if (ptr)
			{
				EnableShared(ptr);
				other.Release();
			}
		}
		
		~TFSharedPtr() noexcept { this->DecrementUse(); }
	
	public:
		
		TFSharedPtr &operator=(const TFSharedPtr &other) noexcept
		{
			TFSharedPtr(other).Swap(*this);
			return *this;
		}
		
		template<typename T>
		TFSharedPtr &operator=(const TFSharedPtr<T> &other) noexcept
		{
			TFSharedPtr(other).Swap(*this);
			return *this;
		}
		
		TFSharedPtr &operator=(TFSharedPtr &&other) noexcept
		{
			TFSharedPtr(Whale::Move(other)).Swap(*this);
			return *this;
		}
		
		template<typename T>
		TFSharedPtr &operator=(TFSharedPtr<T> &&other) noexcept
		{
			TFSharedPtr(Whale::Move(other)).Swap(*this);
			return *this;
		}
		
		template<typename T>
		TFSharedPtr &operator=(TFUniquePtr<T> &&other) noexcept
		{
			TFSharedPtr(Whale::Move(other)).Swap(*this);
			return *this;
		}
		
		ElemT *operator->() const noexcept { return this->ptr; }
		
		ElemT &operator*() const noexcept { return *this->ptr; }
		
		ElemT &operator[](SizeT index) const noexcept { return this->ptr[index]; }
		
		explicit operator Bool() { return this->ptr != nullptr; }
	
	public:
		
		///
		/// 重置
		void Reset() noexcept { TFSharedPtr().Swap(*this); }
		
		///
		/// 重置
		/// \param ptrArg 指针
		void Reset(ElemT *ptrArg) noexcept { TFSharedPtr(ptrArg).Swap(*this); }
		
		///
		/// 交换数据
		/// \param other
		void Swap(TFSharedPtr &other) noexcept { this->BaseSwap(other); }
	
	private:
		
		template<class T>
		void EnableShared(T *ptrArg) noexcept;
		
	};
	
	template<class ElemT>
	class WHALE_API TFWeakPtr : public _TFPtrBase<ElemT>
	{
	public:
		
		template<class> friend
		class TFWeakPtr;
	
	public:
		
		constexpr TFWeakPtr() noexcept = default;
		
		TFWeakPtr(const TFWeakPtr &other) noexcept
		{
			this->WeaklyConstructFrom(other);
		}
		
		template<class T>
		TFWeakPtr(const TFSharedPtr<T> &other) noexcept // NOLINT(*-explicit-constructor)
		{
			this->WeaklyConstructFrom(other);
		}
		
		template<class T>
		TFWeakPtr(const TFWeakPtr<T> &other) noexcept // NOLINT(*-explicit-constructor)
		{
			this->WeaklyConstructFrom(other);
		}
		
		TFWeakPtr(TFWeakPtr &&other) noexcept
		{
			this->MoveConstructFrom(Whale::Move(other));
		}
		
		template<class T>
		TFWeakPtr(TFWeakPtr<T> &&other) noexcept // NOLINT(*-explicit-constructor)
		{
			this->MoveConstructFrom(Whale::Move(other));
		}
		
		~TFWeakPtr() noexcept { this->DecrementWeak(); }
	
	public:
		
		TFWeakPtr &operator=(const TFWeakPtr &other) noexcept
		{
			TFWeakPtr(other).Swap(*this);
			return *this;
		}
		
		template<typename T>
		TFWeakPtr &operator=(const TFWeakPtr<T> &other) noexcept
		{
			TFWeakPtr(other).Swap(*this);
			return *this;
		}
		
		TFWeakPtr &operator=(TFWeakPtr &&other) noexcept
		{
			TFWeakPtr(Whale::Move(other)).Swap(*this);
			return *this;
		}
		
		template<typename T>
		TFWeakPtr &operator=(TFWeakPtr<T> &&other) noexcept
		{
			TFWeakPtr(Whale::Move(other)).Swap(*this);
			return *this;
		}
		
		template<typename T>
		TFWeakPtr &operator=(TFSharedPtr<T> &&other) noexcept
		{
			TFWeakPtr(Whale::Move(other)).Swap(*this);
			return *this;
		}
	
	public:
		
		///
		/// 重置
		void Reset() noexcept { TFWeakPtr{}.Swap(*this); }
		
		///
		/// 交换数据
		/// \param other
		void Swap(TFWeakPtr &other) noexcept { this->BaseSwap(other); }
		
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
		TFSharedPtr<ElemT> Lock() const noexcept
		{
			TFSharedPtr<ElemT> result;
			(void) result.ConstructFromWeak(*this);
			return result;
		}
		
	};
	
	
} // Whale

#include "Memory.inl"
