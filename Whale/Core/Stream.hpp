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
		
		TIInputStream() noexcept = default;
		
		TIInputStream(const TIInputStream &) = delete;
		
		TIInputStream &operator=(const TIInputStream &) = delete;
	
	public:
		
		virtual ElemT Peek() = 0;
		
		virtual ElemT Get() = 0;
		
		virtual ElemT UnGet() = 0;
		
	};
	
	
	///
	/// 输出流
	template<class ElemT>
	class TIOutputStream
	{
	public:
		
		TIOutputStream() noexcept = default;
		
		TIOutputStream(const TIOutputStream &) = delete;
		
		TIOutputStream &operator=(const TIOutputStream &) = delete;
	
	public:
		
		virtual TIOutputStream &Put(ElemT elem) = 0;
		
		virtual TIOutputStream &Flush() = 0;
		
	};
	
	///
	/// 输入输出流
	template<class ElemT>
	class TIStream : public TIInputStream<ElemT>, public TIOutputStream<ElemT>
	{
	public:
		
		TIStream() noexcept = default;
		
		TIStream(const TIStream &) = delete;
		
		TIStream &operator=(const TIStream &) = delete;
		
	};
	
} // Whale
