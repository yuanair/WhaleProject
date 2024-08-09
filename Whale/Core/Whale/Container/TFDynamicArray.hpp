//
// Created by admin on 2024/8/5.
//

#pragma once

#include "../Utility.hpp"
#include "InitList.hpp"
#include "TIPointerIterator.hpp"
#include "TFReverseIterator.hpp"
#include "TFAllocator.hpp"

namespace Whale::Container
{
	
	/// 非侵入式内存连续动态数组
	template<class ElemT, class AllocatorT = TFAllocator<ElemT>>
	class WHALE_API TFDynamicArray
	{
	public:
		
		using OffsetType = int32;
		
		using FIterator = TIPointerIterator<ElemT, OffsetType>;
		using FConstIterator = TIConstPointerIterator<ElemT, OffsetType>;
		using FReverseIterator = TFReverseIterator<FIterator, OffsetType>;
		using FConstReverseIterator = TFReverseIterator<FConstIterator, OffsetType>;
		
		using FAllocator = AllocatorT;
		
		/// 默认容量
		static constexpr SizeT DefaultCapacity = 0;
	
	public:
		
		TFDynamicArray() noexcept: TFDynamicArray(DefaultCapacity) {}
		
		TFDynamicArray(const std::initializer_list<ElemT> &initializerList)
			: TFDynamicArray(initializerList.begin(), initializerList.end()) {}
		
		TFDynamicArray(const TFDynamicArray &other);
		
		TFDynamicArray(TFDynamicArray &&other) noexcept;
		
		explicit TFDynamicArray(SizeT capacity) noexcept;
		
		TFDynamicArray(const ElemT *start, const ElemT *end);
		
		~TFDynamicArray() noexcept;
	
	public:
		
		TFDynamicArray &operator=(TFDynamicArray other) noexcept;
		
		TFDynamicArray &operator+=(ElemT elem);
		
		ElemT &operator[](SizeT index);
		
		const ElemT &operator[](SizeT index) const;
		
		Bool operator==(const TFDynamicArray &other) const { return Equal(other); }
		
		Bool operator!=(const TFDynamicArray &other) const { return !Equal(other); }
	
	public:
		
		inline FIterator begin() { return FIterator{GetData()}; }
		
		inline FIterator end() { return FIterator{GetData() + GetLength()}; }
		
		inline FConstIterator begin() const { return FConstIterator{GetData()}; }
		
		inline FConstIterator end() const { return FConstIterator{GetData() + GetLength()}; }
		
		inline FConstIterator cbegin() const { return begin(); }
		
		inline FConstIterator cend() const { return end(); }
		
		inline FReverseIterator rbegin() { return FReverseIterator{--end()}; }
		
		inline FReverseIterator rend() { return FReverseIterator{--begin()}; }
		
		inline FConstReverseIterator rbegin() const { return FConstReverseIterator{--end()}; }
		
		inline FConstReverseIterator rend() const { return FConstReverseIterator{--begin()}; }
		
		inline FConstReverseIterator crbegin() const { return rbegin(); }
		
		inline FConstReverseIterator crend() const { return rend(); }
		
		inline Bool IsIn(const FConstIterator &iter) const { return begin() <= iter && iter <= end(); }
	
	public:
		
		/// 获取索引上的元素
		ElemT &At(SizeT index);
		
		/// 获取索引上的元素
		const ElemT &At(SizeT index) const;
		
		/// 获取倒数索引上的元素
		ElemT &AtBack(SizeT index);
		
		/// 获取倒数索引上的元素
		const ElemT &AtBack(SizeT index) const;
		
		/// 是否相等
		Bool Equal(const TFDynamicArray &other) const;
		
		/// 添加元素
		ElemT &Append(ElemT elem);
		
		/// 弹出最后一个元素
		ElemT PopBack();
		
		/// 插入元素
		[[deprecated("unrealized")]]
		ElemT &Insert(ElemT elem, const FConstIterator &where);
		
		/// 清空数组
		void Clear();
		
		/// 清空数组，但不清除分配的空间
		void DestroyAll();
		
		/// 删除
		[[deprecated("unrealized")]]
		void Erase(const FConstIterator &where);
		
		/// 删除
		[[deprecated("unrealized")]]
		void Erase(const FConstIterator &startIter, const FConstIterator &endIter);
		
		/// 改变容量（不应该频繁调用）
		void AdjustCapacity(SizeT capacity);
		
		/// 计算扩容容量
		[[nodiscard]] SizeT CalculateGrowth(SizeT newSize) const;
		
		/// 交换数据
		void Swap(TFDynamicArray &other) noexcept;
	
	public:
		
		/// 扩容到最少还可容下一个元素
		inline void Expansion() { AdjustCapacity(CalculateGrowth(m_capacity + 1)); }
		
		/// 保证容量
		inline void Reserve(SizeT capacity)
		{
			if (m_capacity >= capacity) return;
			AdjustCapacity(CalculateGrowth(capacity));
		}
	
	public:
		
		/// 改变长度
		template<class... Args>
		void AdjustLength(SizeT length, Args &&... args);
		
		/// 从迭代器拷贝
		template<class IterT>
		void CopyFrom(const IterT &beginIt, const IterT &endIt);
	
	public:
		
		/// 获取分配器
		[[nodiscard]] FAllocator &GetAllocator() noexcept { return m_allocator; }
		
		/// 获取分配器
		[[nodiscard]] const FAllocator &GetAllocator() const noexcept { return m_allocator; }
		
		/// 获取容量
		[[nodiscard]] SizeT GetCapacity() const noexcept { return m_capacity; }
		
		/// 获取长度
		[[nodiscard]] SizeT GetLength() const noexcept { return m_length; }
		
		/// 获取数据
		[[nodiscard]] ElemT *GetData() noexcept { return m_data; }
		
		/// 获取数据
		[[nodiscard]] const ElemT *GetData() const noexcept { return m_data; }
		
		/// 是否为空数组
		[[nodiscard]] Bool IsEmpty() const noexcept { return m_length == 0; }
	
	private:
		
		FAllocator m_allocator;
		
		SizeT m_capacity;
		
		SizeT m_length;
		
		ElemT *m_data;
		
	};
	
	
	template<class ElemT>
	inline WHALE_API void Swap(TFDynamicArray<ElemT> &a, TFDynamicArray<ElemT> &b) noexcept { a.Swap(b); }
	
	
} // Whale

#include "TFDynamicArray.inl"
