//
// Created by admin on 2024/8/5.
//

#pragma once

#include "../Utility.hpp"
#include "InitList.hpp"
#include "TIPointerIterator.hpp"
#include "TFReverseIterator.hpp"

namespace Whale
{
	
	/// 可变长数组
	template<class ElemT>
	class WHALE_API TFVector
	{
	public:
		
		using SizeType = int32;
		
		using FIterator = TIPointerIterator<ElemT>;
		using FConstIterator = TIPointerIterator<const ElemT>;
		using FReverseIterator = TFReverseIterator<TIPointerIterator<ElemT>>;
		using FConstReverseIterator = TFReverseIterator<TIPointerIterator<const ElemT>>;
	
	public:
		
		TFVector();
		
		TFVector(const TFVector &other);
		
		TFVector(TFVector &&other);
		
		TFVector(const std::initializer_list<ElemT> &initializerList);
		
		~TFVector();
	
	public:
		
		TFVector &operator=(TFVector other);
		
		ElemT &operator[](SizeT index);
		
		const ElemT &operator[](SizeT index) const;
		
		Bool operator==(TFVector other) const;
		
		Bool operator!=(TFVector other) const;
	
	public:
		
		FIterator Begin();
		
		FIterator End();
		
		FConstIterator Begin() const;
		
		FConstIterator End() const;
		
		FReverseIterator RBegin();
		
		FReverseIterator REnd();
		
		FConstReverseIterator RBegin() const;
		
		FConstReverseIterator REnd() const;
		
		inline FIterator begin() { return Begin(); }
		
		inline FIterator end() { return End(); }
		
		inline FConstIterator begin() const { return Begin(); }
		
		inline FConstIterator end() const { return End(); }
		
		inline FReverseIterator rbegin() { return RBegin(); }
		
		inline FReverseIterator rend() { return REnd(); }
		
		inline FConstReverseIterator rbegin() const { return RBegin(); }
		
		inline FConstReverseIterator rend() const { return REnd(); }
	
	public:
		
		ElemT &At(SizeT index);
		
		ElemT &At(SizeT index) const;
		
		Bool Equal(const TFVector &other) const;
		
		ElemT &Append(ElemT elem);
		
		ElemT &Insert(ElemT elem);
		
		void Remove(const ElemT &elem);
		
		void Erase(const ElemT &elem);
		
		void Swap(TFVector &other);
	
	
	private:
	
	
	};
	
} // Whale
