
#include "CRT.hpp"

namespace Whale
{
	
	
	template<class ElemT>
	template<class T>
	void TFSharedPtr<ElemT>::EnableShared(T *ptrArg) noexcept
	{
		this->m_ptr      = ptrArg;
		this->m_useCount = WHALE_NEW_CLIENT _TFUseCount<T>(ptrArg);
	}
	
	template<class ElemT, class... Args>
	TFUniquePtr<ElemT> MakeUnique(Args &&... args)
	{
		return TFUniquePtr<ElemT>(WHALE_NEW_CLIENT ElemT(Forward<Args>(args)...));
	}
	
	template<class ElemT, class... Args>
	TFSharedPtr<ElemT> MakeShared(Args &&... args)
	{
		return TFSharedPtr<ElemT>(WHALE_NEW_CLIENT ElemT(Forward<Args>(args)...));
	}
	
	template<class T1, class T2>
	TFSharedPtr<T1> StaticPointerCast(const TFSharedPtr<T2> &other) noexcept
	{
		const auto ptr = static_cast<T1 *>(other.Get());
		return TFSharedPtr<T1>(other, ptr);
	}
	
	template<class T1, class T2>
	TFSharedPtr<T1> StaticPointerCast(TFSharedPtr<T2> &&other) noexcept
	{
		const auto ptr = static_cast<T1 *>(other.Get());
		return TFSharedPtr<T1>(Whale::Move(other), ptr);
	}
	
	template<class T1, class T2>
	TFSharedPtr<T1> ConstPointerCast(const TFSharedPtr<T2> &other) noexcept
	{
		const auto ptr = const_cast<T1 *>(other.Get());
		return TFSharedPtr<T1>(other, ptr);
	}
	
	template<class T1, class T2>
	TFSharedPtr<T1> ConstPointerCast(TFSharedPtr<T2> &&other) noexcept
	{
		const auto ptr = const_cast<T1 *>(other.Get());
		return TFSharedPtr<T1>(Whale::Move(other), ptr);
	}
	
	template<class T1, class T2>
	TFSharedPtr<T1> ReinterpretPointerCast(const TFSharedPtr<T2> &other) noexcept
	{
		const auto ptr = reinterpret_cast<T1 *>(other.Get());
		return TFSharedPtr<T1>(other, ptr);
	}
	
	template<class T1, class T2>
	TFSharedPtr<T1> ReinterpretPointerCast(TFSharedPtr<T2> &&other) noexcept
	{
		const auto ptr = reinterpret_cast<T1 *>(other.Get());
		return TFSharedPtr<T1>(Whale::Move(other), ptr);
	}
	
	template<class T1, class T2>
	TFSharedPtr<T1> DynamicPointerCast(const TFSharedPtr<T2> &other) noexcept
	{
		const auto ptr = dynamic_cast<T1 *>(other.Get());
		if (ptr)return TFSharedPtr<T1>(other, ptr);
		return {};
	}
	
	template<class T1, class T2>
	TFSharedPtr<T1> DynamicPointerCast(TFSharedPtr<T2> &&other) noexcept
	{
		const auto ptr = dynamic_cast<T1 *>(other.Get());
		if (ptr)return TFSharedPtr<T1>(Whale::Move(other), ptr);
		return {};
	}
	
}
