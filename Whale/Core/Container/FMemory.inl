
#include "Whale/Core/Tool/FCRT.hpp"

namespace Whale
{
	
	///
	/// 创建
	/// \return 独有指针
	template<class ElemT, class... Args>
	FTUniquePtr<ElemT> MakeUnique(Args &&... args)
	{
		return FTUniquePtr<ElemT>(WHALE_DBG_NEW ElemT(Forward<Args>(args)...));
	}
	
	///
	/// 创建
	/// \return 共享指针
	template<class ElemT, class... Args>
	FTSharedPtr<ElemT> MakeShared(Args &&... args)
	{
		return FTSharedPtr<ElemT>(WHALE_DBG_NEW ElemT(Forward<Args>(args)...));
	}
	
	template<class ElemT>
	template<class T>
	void FTSharedPtr<ElemT>::EnableShared(T *ptrArg) noexcept
	{
		this->ptr = ptrArg;
		this->useCount = WHALE_DBG_NEW _FTUseCount<T>(ptrArg);
	}
	
}
