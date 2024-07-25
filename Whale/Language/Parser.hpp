//
// Created by admin on 2024/7/24.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"
#include "Whale/Core/Stream.hpp"
#include "Whale/Language/TIParser.hpp"

namespace Whale
{
	
	///
	/// 语法分析错误
	enum EParserError
	{
		EParserErrorUnknown = 0
	};
	
	///
	/// 语法分析错误
	template<class ElemT>
	class WHALE_API TFParserError
	{
	public:
		
		using String = Container::TFString<ElemT>;
	
	public:
		
		TFParserError() : pos(), error(EParserErrorUnknown), message() {}
		
		TFParserError(const FTokenPos &pos, EParserError error, const String &message) : pos(pos), error(error),
		                                                                                 message(message) {}
	
	public:
		
		FTokenPos pos;
		
		EParserError error;
		
		String message;
		
	};
	
	///
	/// 语法分析错误
	template<class ElemT>
	class TWParser : public WObject, public TIParser<ElemT>
	{
	public:
		
		explicit TWParser(TILexer<ElemT> &lexer) : m_lexer(lexer) {}
	
	public:
		
		TILexer<ElemT> &m_lexer;
		
	};
	
} // Whale
