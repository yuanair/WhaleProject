//
// Created by admin on 2024/8/10.
//

#pragma once

#include "../Utility.hpp"

namespace Whale::Container
{
	
	/// 静态数组
	template<class ElemT, SizeT TheLength>
	class WHALE_API TFStaticArray
	{
	public:
		
		using ElemType = ElemT;
	
	public:
		
		static constexpr SizeT m_length = TheLength;
	
	public:
		
		TFStaticArray();
		
		TFStaticArray(const TFStaticArray &other);
		
		TFStaticArray(TFStaticArray &&other);
		
		TFStaticArray(const std::initializer_list<ElemT> &initializerList);
		
		~TFStaticArray() noexcept;
	
	public:
		
		TFStaticArray &operator=(const TFStaticArray &other);
		
		TFStaticArray &operator=(TFStaticArray &&other);
		
		ElemT &operator[](SizeT index) { return At(index); }
		
		const ElemT &operator[](SizeT index) const { return At(index); }
		
		inline Bool operator==(const TFStaticArray &other) const { return Equal(other); }
		
		inline Bool operator!=(const TFStaticArray &other) const { return !Equal(other); }
	
	public:
		
		ElemT &At(SizeT index);
		
		const ElemT &At(SizeT index) const;
		
		ElemT &AtBack(SizeT index);
		
		const ElemT &AtBack(SizeT index) const;
		
		Bool Equal(const TFStaticArray &other) const;
		
		void Swap(TFStaticArray &other);
	
	public:
		
		[[nodiscard]] SizeT GetLength() const { return m_length; }
	
	private:
		
		ElemT m_arr[TheLength];
		
	};
	
	template<class ElemT, SizeT TheLength>
	ElemT &TFStaticArray<ElemT, TheLength>::At(SizeT index)
	{
		WHALE_ASSERT(index < TheLength);
		return m_arr[index];
	}
	
	template<class ElemT, SizeT TheLength>
	const ElemT &TFStaticArray<ElemT, TheLength>::At(SizeT index) const
	{
		WHALE_ASSERT(index < TheLength);
		return m_arr[index];
	}
	
	template<class ElemT, SizeT TheLength>
	ElemT &TFStaticArray<ElemT, TheLength>::AtBack(SizeT index)
	{
		WHALE_ASSERT(index < TheLength);
		return m_arr[TheLength - index - 1];
	}
	
	template<class ElemT, SizeT TheLength>
	const ElemT &TFStaticArray<ElemT, TheLength>::AtBack(SizeT index) const
	{
		WHALE_ASSERT(index < TheLength);
		return m_arr[TheLength - index - 1];
	}
	
} // Whale
