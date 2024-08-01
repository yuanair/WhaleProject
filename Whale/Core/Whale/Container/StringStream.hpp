//
// Created by admin on 2024/7/23.
//

#pragma once

#include "../Stream.hpp"
#include "TFString.hpp"


namespace Whale::Container
{
	
	///
	/// 字符串流
	template<class ElemT>
	class TWStringStreamReader : public TIStreamReader<ElemT>
	{
	public:
		
		using String = TFString<ElemT>;
	
	public:
		
		TWStringStreamReader() : m_buffer(), m_index(0) {}
		
		explicit TWStringStreamReader(String buffer) : m_buffer(Whale::Move(buffer)), m_index(0) {}
		
		~TWStringStreamReader() = default;
	
	public:
		
		[[nodiscard]] Bool Good() const noexcept override
		{
			return m_index < m_buffer.GetLength();
		}
		
		[[nodiscard]] Bool Bad() const noexcept override
		{
			return m_index >= m_buffer.GetLength();
		}
		
		ElemT Peek() noexcept override
		{
			if (Bad()) return 0;
			return m_buffer[m_index];
		}
		
		ElemT Read() noexcept override
		{
			if (Bad()) return 0;
			return m_buffer[m_index++];
		}
	
	private:
		
		String m_buffer;
		
		SizeT m_index;
		
	};
	
	using StringStreamReaderA = TWStringStreamReader<CharA>;
	using StringStreamReaderW = TWStringStreamReader<CharW>;
	using StringStreamReaderT = TWStringStreamReader<CharT>;
	
} // Whale
