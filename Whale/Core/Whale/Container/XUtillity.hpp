//
// Created by admin on 2024/8/7.
//

#pragma once

#include "../Utility.hpp"

namespace Whale::Container
{
	
	/// 填充
	template<class ElemT, class Iter>
	WHALE_API inline void Fill(const ElemT &elem, const Iter &start, const Iter &end)
	{
		for (Iter iter = start; iter != end; ++iter)
		{
			*iter = elem;
		}
	}
	
	/// 查找
	template<class ElemT, class Iter>
	WHALE_API inline Iter Find(const ElemT &elem, const Iter &start, const Iter &end)
	{
		for (Iter iter = start; iter != end; ++iter)
		{
			if (elem == *iter) return iter;
		}
		return end;
	}
	
	/// 拷贝
	template<class InIter, class OutIter>
	WHALE_API inline void Copy(const InIter &start, const InIter &end, OutIter &dest)
	{
		for (InIter iter = start; iter != end; ++iter, ++dest)
		{
			*dest = *iter;
		}
	}
	
	/// 移动
	template<class InIter, class OutIter>
	WHALE_API inline void Move(const InIter &start, const InIter &end, OutIter &dest)
	{
		for (InIter iter = start; iter != end; ++iter, ++dest)
		{
			*dest = Whale::Move(*iter);
		}
	}
	
	/// 替换
	template<class ElemT, class Iter>
	WHALE_API inline SizeT Replace(const ElemT &oldElem, const ElemT &newElemT, const Iter &start, const Iter &end)
	{
		SizeT     count = 0;
		for (Iter iter  = start; iter != end; ++iter)
		{
			if (oldElem == *iter)
			{
				*iter = newElemT;
				++count;
			}
		}
		return count;
	}
	
} // Whale
