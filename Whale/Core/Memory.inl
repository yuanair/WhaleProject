
#include "CRT.hpp"

namespace Whale
{
	
	///
	/// 创建
	/// \return 独有指针
	template<class ElemT, class... Args>
	TFUniquePtr<ElemT> MakeUnique(Args &&... args)
	{
		return TFUniquePtr<ElemT>(WHALE_NEW_CLIENT ElemT(Forward<Args>(args)...));
	}
	
	///
	/// 创建
	/// \return 共享指针
	template<class ElemT, class... Args>
	TFSharedPtr<ElemT> MakeShared(Args &&... args)
	{
		return TFSharedPtr<ElemT>(WHALE_NEW_CLIENT ElemT(Forward<Args>(args)...));
	}
	
	template<class ElemT>
	template<class T>
	void TFSharedPtr<ElemT>::EnableShared(T *ptrArg) noexcept
	{
		this->ptr = ptrArg;
		this->useCount = WHALE_NEW_CLIENT _TFUseCount<T>(ptrArg);
	}
	
}
