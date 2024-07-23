//
// Created by admin on 2024/7/19.
//

#pragma once

#include "TypeDef.hpp"
#include "WObject.hpp"
#include "IGoodAndBad.hpp"
#include "./Container/TFString.hpp"

namespace Whale
{
	
	
	///
	/// 输入流
	template<class ElemT>
	class TIInputStream : public virtual IGoodAndBad
	{
	public:
		
		using String = Container::TFString<ElemT>;
	
	public:
		
		TIInputStream() noexcept = default;
		
		TIInputStream(const TIInputStream &) = delete;
		
		TIInputStream &operator=(const TIInputStream &) = delete;
	
	public:
		
		virtual TIInputStream &Peek(ElemT &elem) noexcept = 0;
		
		virtual TIInputStream &Get(ElemT &elem) noexcept = 0;
		
		virtual TIInputStream &UnGet(ElemT &elem) noexcept = 0;
		
	};
	
	
	///
	/// 输出流
	template<class ElemT>
	class TIOutputStream : public virtual IGoodAndBad
	{
	public:
		
		using String = Container::TFString<ElemT>;
	
	public:
		
		TIOutputStream() noexcept = default;
		
		TIOutputStream(const TIOutputStream &) = delete;
		
		TIOutputStream &operator=(const TIOutputStream &) = delete;
	
	public:
		
		virtual TIOutputStream &Put(ElemT elem) noexcept = 0;
		
		virtual TIOutputStream &Flush() noexcept = 0;
		
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
