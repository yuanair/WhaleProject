//
// Created by admin on 2024/7/17.
//

#pragma once

#include "TypeDef.hpp"
#include "Utility.hpp"
#include "FIntrinsics.hpp"
#include "Exception.hpp"
#include "IGoodAndBad.hpp"

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
	class WHALE_API TFUniquePtr : public IGoodAndBad
	{
		
		template<class> friend
		class TFUniquePtr;
	
	public:
		
		constexpr TFUniquePtr() noexcept: ptr(nullptr) {}
		
		constexpr TFUniquePtr(NullPtrT) noexcept: ptr(nullptr) {} // NOLINT(*-explicit-constructor)
		
		explicit TFUniquePtr(ElemT *ptr) noexcept: ptr(ptr) {}
		
		TFUniquePtr(const TFUniquePtr &other) = delete;
		
		TFUniquePtr(TFUniquePtr &&other) noexcept: ptr(other.Release()) {}
		
		template<typename T>
		TFUniquePtr(const TFUniquePtr<T> &other) noexcept: ptr(other.ptr) {} // NOLINT(*-explicit-constructor)
		
		template<typename T>
		TFUniquePtr(TFUniquePtr<T> &&other) noexcept: ptr(other.Release()) {} // NOLINT(*-explicit-constructor)
		
		~TFUniquePtr() noexcept override { Reset(); }
	
	public:
		
		Bool operator==(const TFUniquePtr &other) const noexcept { return this->GetPtr() == other.GetPtr(); }
		
		Bool operator!=(const TFUniquePtr &other) const noexcept { return this->GetPtr() != other.GetPtr(); }
		
		TFUniquePtr &operator=(const TFUniquePtr &other) = delete;
		
		TFUniquePtr &operator=(TFUniquePtr &&other) noexcept
		{
			Reset(other.Release());
			return *this;
		}
		
		ElemT *operator->() const noexcept { return this->ptr; }
		
		ElemT &operator*() const noexcept { return *this->ptr; }
		
		ElemT &operator[](SizeT index) const noexcept { return this->ptr[index]; }
	
	public:
		
		[[nodiscard]] Bool Good() const noexcept override { return this->ptr != nullptr; }
		
		[[nodiscard]] Bool Bad() const noexcept override { return this->ptr == nullptr; }
		
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
	class WHALE_API _TFPtrBase : public IGoodAndBad // NOLINT(*-reserved-identifier)
	{
	public:
		
		template<class> friend
		class _TFPtrBase; // NOLINT(*-reserved-identifier)
	
	protected:
		
		constexpr _TFPtrBase() noexcept
			: m_ptr(nullptr), m_useCount(nullptr) {}
		
		~_TFPtrBase() override = default;
	
	public:
		
		[[nodiscard]] Bool Good() const noexcept override { return this->m_ptr != nullptr; }
		
		[[nodiscard]] Bool Bad() const noexcept override { return this->m_ptr == nullptr; }
		
		///
		/// \return 获取指针
		[[nodiscard]] ElemT *Get() const noexcept
		{
			return this->m_ptr;
		}
		
		///
		/// \return 获取使用引用计数
		[[nodiscard]] AtomicCounterT GetUseCount() const noexcept
		{
			return this->m_useCount ? this->m_useCount->GetUses() : 0;
		}
		
		///
		/// \return 获取查看引用计数
		[[nodiscard]] AtomicCounterT GetWeakCount() const noexcept
		{
			return this->m_useCount ? this->m_useCount->GetWeaks() : 0;
		}
	
	protected:
		
		template<class T>
		void MoveConstructFrom(_TFPtrBase<T> &&other)
		{
			this->m_ptr      = other.m_ptr;
			this->m_useCount = other.m_useCount;
			other.m_ptr      = nullptr;
			other.m_useCount = nullptr;
		}
		
		template<class T>
		void CopyConstructFrom(const TFSharedPtr<T> &other)
		{
			other.IncrementUse();
			this->m_ptr      = other.m_ptr;
			this->m_useCount = other.m_useCount;
		}
		
		template<class T>
		void AliasConstructFrom(const TFSharedPtr<T> &other, ElemT *ptr) noexcept
		{
			other.IncrementUse();
			this->m_ptr      = ptr;
			this->m_useCount = other.m_useCount;
		}
		
		template<class T>
		void AliasMoveConstructFrom(TFSharedPtr<T> &&other, ElemT *ptr) noexcept
		{
			this->m_ptr      = ptr;
			this->m_useCount = other.m_useCount;
			other.m_ptr      = nullptr;
			other.m_useCount = nullptr;
		}
		
		template<class T>
		bool ConstructFromWeak(const TFWeakPtr<T> &other) noexcept
		{
			if (other.m_useCount && other.m_useCount->IncrementUseNoZero())
			{
				this->m_ptr      = other.m_ptr;
				this->m_useCount = other.m_useCount;
				return true;
			}
			
			return false;
		}
		
		template<class T>
		void WeaklyConstructFrom(const _TFPtrBase<T> &other) noexcept
		{
			if (other.m_useCount)
			{
				this->m_ptr      = other.m_ptr;
				this->m_useCount = other.m_useCount;
				this->m_useCount->IncrementWeak();
			}
			else
			{
				WHALE_ASSERT(!this->m_ptr && !this->m_useCount, L"!this->m_ptr && !this->m_useCount");
			}
		}
		
		void IncrementUse() const noexcept { if (this->m_useCount) this->m_useCount->IncrementUse(); }
		
		void IncrementWeak() const noexcept { if (this->m_useCount) this->m_useCount->IncrementWeak(); }
		
		void DecrementUse() noexcept { if (this->m_useCount) this->m_useCount->DecrementUse(); }
		
		void DecrementWeak() noexcept { if (this->m_useCount) this->m_useCount->DecrementWeak(); }
		
		void BaseSwap(_TFPtrBase &other) noexcept
		{
			Whale::Swap(this->m_ptr, other.m_ptr);
			Whale::Swap(this->m_useCount, other.m_useCount);
		}
	
	protected:
		
		[[nodiscard]] ElemT *GetPtr() const noexcept { return this->m_ptr; }
	
	protected:
		
		ElemT *m_ptr;
		
		_FUseCountBase *m_useCount;
		
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
		
		template<class T>
		TFSharedPtr(const TFSharedPtr<T> &other, ElemT *ptr) noexcept
		{
			this->AliasConstructFrom(other, ptr);
		}
		
		template<class T>
		TFSharedPtr(TFSharedPtr<T> &&other, ElemT *ptr) noexcept
		{
			this->AliasMoveConstructFrom(Whale::Move(other), ptr);
		}
		
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
				throw FBadWeakPtrException();
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
		
		~TFSharedPtr() noexcept override { this->DecrementUse(); }
	
	public:
		
		Bool operator==(const TFSharedPtr &other) const noexcept { return this->GetPtr() == other.GetPtr(); }
		
		Bool operator!=(const TFSharedPtr &other) const noexcept { return this->GetPtr() != other.GetPtr(); }
		
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
		
		ElemT *operator->() const noexcept { return this->m_ptr; }
		
		ElemT &operator*() const noexcept { return *this->m_ptr; }
		
		ElemT &operator[](SizeT index) const noexcept { return this->m_ptr[index]; }
		
		explicit operator Bool() { return this->m_ptr != nullptr; }
	
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
		
		~TFWeakPtr() noexcept override { this->DecrementWeak(); }
	
	public:
		
		Bool operator==(const TFWeakPtr &other) const noexcept { return this->GetPtr() == other.GetPtr(); }
		
		Bool operator!=(const TFWeakPtr &other) const noexcept { return this->GetPtr() != other.GetPtr(); }
		
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
	
	
	///
	/// 创建
	/// \return 独有指针
	template<class ElemT, class... Args>
	TFUniquePtr<ElemT> MakeUnique(Args &&... args);
	
	///
	/// 创建
	/// \return 共享指针
	template<class ElemT, class... Args>
	TFSharedPtr<ElemT> MakeShared(Args &&... args);
	
	/// 静态复制转换指针
	template<class T1, class T2>
	TFSharedPtr<T1> StaticPointerCast(const TFSharedPtr<T2> &other) noexcept;
	
	/// 静态移动转换指针
	template<class T1, class T2>
	TFSharedPtr<T1> StaticPointerCast(TFSharedPtr<T2> &&other) noexcept;
	
	/// const复制转换指针
	template<class T1, class T2>
	TFSharedPtr<T1> ConstPointerCast(const TFSharedPtr<T2> &other) noexcept;
	
	/// const移动转换指针
	template<class T1, class T2>
	TFSharedPtr<T1> ConstPointerCast(TFSharedPtr<T2> &&other) noexcept;
	
	/// 强制复制转换指针
	template<class T1, class T2>
	TFSharedPtr<T1> ReinterpretPointerCast(const TFSharedPtr<T2> &other) noexcept;
	
	/// 强制移动转换指针
	template<class T1, class T2>
	TFSharedPtr<T1> ReinterpretPointerCast(TFSharedPtr<T2> &&other) noexcept;
	
	/// 动态复制转换指针
	template<class T1, class T2>
	TFSharedPtr<T1> DynamicPointerCast(const TFSharedPtr<T2> &other) noexcept;
	
	/// 动态移动转换指针
	template<class T1, class T2>
	TFSharedPtr<T1> DynamicPointerCast(TFSharedPtr<T2> &&other) noexcept;
	
} // Whale

#include "Memory.inl"
