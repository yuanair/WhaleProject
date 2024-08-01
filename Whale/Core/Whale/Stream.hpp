//
// Created by admin on 2024/7/19.
//

#pragma once

#include "TypeDef.hpp"
#include "WObject.hpp"
#include "IGoodAndBad.hpp"
#include "Container/TFString.hpp"

namespace Whale
{
	
	
	///
	/// 读取流
	template<class ElemT>
	class TIStreamReader : public virtual IGoodAndBad
	{
	public:
		
		TIStreamReader() noexcept = default;
		
		TIStreamReader(const TIStreamReader &) = delete;
		
		TIStreamReader &operator=(const TIStreamReader &) = delete;
		
		virtual ~TIStreamReader() noexcept = default;
	
	public:
		
		virtual ElemT Peek() noexcept = 0;
		
		virtual ElemT Read() noexcept = 0;
		
	};
	
	
	///
	/// 写入流
	template<class ElemT>
	class TIStreamWriter : public virtual IGoodAndBad
	{
	public:
		
		TIStreamWriter() noexcept = default;
		
		TIStreamWriter(const TIStreamWriter &) = delete;
		
		TIStreamWriter &operator=(const TIStreamWriter &) = delete;
		
		virtual ~TIStreamWriter() noexcept = default;
	
	public:
		
		virtual TIStreamWriter &Write(ElemT elem) noexcept = 0;
		
		virtual TIStreamWriter &Flush() noexcept = 0;
		
	};
	
	///
	/// 输入输出流
	template<class ReadT, class WriteT>
	class TIStream : public TIStreamReader<ReadT>, public TIStreamWriter<WriteT>
	{
	public:
		
		TIStream() noexcept = default;
		
		TIStream(const TIStream &) = delete;
		
		TIStream &operator=(const TIStream &) = delete;
		
		virtual ~TIStream() noexcept = default;
		
	};
	
} // Whale
