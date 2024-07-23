//
// Created by admin on 2024/7/22.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"
#include "Whale/Core/Stream.hpp"
#include "Whale/Language/Lexer.hpp"

namespace Whale::Json
{
	
	///
	/// Json词法分析器
	template<class ElemT>
	class WLexer : public WObject, public TILexer<ElemT>
	{
	public:
		
		explicit WLexer(TIInputStream<ElemT> &inputStream) : m_inputStream(inputStream) {}
	
	public:
		
		TFUniquePtr<TWToken<ElemT>> Get() noexcept override;
	
	private:
		
		TIInputStream<ElemT> &m_inputStream;
		
	};
	
}
