//
// Created by admin on 2024/7/19.
//

#pragma once

#include "TypeDef.hpp"
#include "Whale/Core/Container/TFString.hpp"
#include "WObject.hpp"

namespace Whale
{
	
	
	///
	/// 输入流
	template<class ElemT>
	class TIInputStream
	{
	public:
		
		using String = Container::TFString<ElemT>;
	
	public:
		
		TIInputStream() noexcept = default;
		
		TIInputStream(const TIInputStream &) = delete;
		
		TIInputStream &operator=(const TIInputStream &) = delete;
	
	public:
		
		virtual Bool Get(ElemT &elem) = 0;
		
		virtual Bool UnGet(ElemT &elem) = 0;
		
		virtual Bool Read(String &elem) = 0;
		
	};
	
	
	///
	/// 输出流
	template<class ElemT>
	class TIOutputStream
	{
	public:
		
		using String = Container::TFString<ElemT>;
	
	public:
		
		TIOutputStream() noexcept = default;
		
		TIOutputStream(const TIOutputStream &) = delete;
		
		TIOutputStream &operator=(const TIOutputStream &) = delete;
	
	public:
		
		virtual Bool Put(ElemT elem) = 0;
		
		virtual Bool Flush() = 0;
		
	};
	
	///
	/// 输入输出流
	template<class ElemT>
	class TIStream : public TIInputStream<ElemT>, public TIOutputStream<ElemT>
	{
	public:
		
		using String = Container::TFString<ElemT>;
	
	public:
		
		TIStream() noexcept = default;
		
		TIStream(const TIStream &) = delete;
		
		TIStream &operator=(const TIStream &) = delete;
		
	};
	
} // Whale
