//
// Created by admin on 2024/7/22.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"
#include "Whale/Core/WObject.hpp"
#include "Whale/Core/Container/TFString.hpp"

namespace Whale
{
	
	///
	/// 符号位置
	struct WHALE_API FTokenPos
	{
		
		/// 行
		SizeT line = 0;
		
		/// 列
		SizeT column = 0;
		
	};
	
	///
	/// 符号类型
	enum ETokenType
	{
		ETokenTypeEOF              = -1,
		ETokenTypeIllegal          = 0,
		ETokenTypeIdentifier       = 1, // identifier
		ETokenTypeString           = 2, // string
		ETokenTypeChar             = 3, // char
		ETokenTypeNumber           = 4, // number
		//
		ETokenTypeExclamationPoint = '!',
		// ETokenTypeString            = '"', // string
		ETokenTypeWellNumber       = '#',
		ETokenTypeDollarSign       = '$',
		ETokenTypePerCent          = '%',
		ETokenTypeAmpersand        = '&',
		// ETokenTypeChar              = '\'', // char
		ETokenTypeParenLeft        = '(',
		ETokenTypeParenRight       = ')',
		ETokenTypeAsterisk         = '*',
		ETokenTypePlusSign         = '+',
		ETokenTypeComma            = ',',
		ETokenTypeSub              = '-',
		ETokenTypePoint            = '.',
		ETokenTypeSlash            = '/',
		// ETokenTypeNumber            = '0', // number
		ETokenTypeColon            = ':',
		ETokenTypeSemicolon        = ';',
		ETokenTypeLessThanSign     = '<',
		ETokenTypeEqualSign        = '=',
		ETokenTypeGreaterThanSign  = '>',
		ETokenTypeQuestionMark     = '?',
		ETokenTypeAtSign           = '@',
		//
		ETokenTypeBracketLeft      = '[',
		ETokenTypeBackslash        = '\\',
		ETokenTypeBracketRight     = ']',
		ETokenTypeBracketCaret     = '^',
		ETokenTypeBracketUnderline = '_',
		ETokenTypeBackquote        = '`',
		//
		ETokenTypeBraceLeft        = '{',
		ETokenTypeOr               = '|',
		ETokenTypeBraceRight       = '}',
		ETokenTypeTilde            = '~'
	};
	
	///
	/// 符号类型数据
	template<class ElemT>
	struct FTokenTypeData
	{
	public:
		
		using String = Container::TFString<ElemT>;
	
	public:
		
		ETokenType type;
		
		String name;
		
	};
	
	///
	/// 符号
	template<class ElemT>
	class WHALE_API TWToken
	{
	public:
		
		using String = Container::TFString<ElemT>;
	
	public:
		
		TWToken(FTokenPos pos, ETokenType type, String str) : m_pos(Whale::Move(pos)), m_type(type),
		                                                      m_str(Whale::Move(str)) {}
	
	public:
		
		FTokenPos m_pos;
		
		ETokenType m_type;
		
		String m_str;
		
	};
	
	#if false
	
	///
	/// 符号
	template<class ElemT>
	class WHALE_API TWToken : public WObject
	{
	public:
		
		using String = Container::TFString<ElemT>;
	
	public:
		
		explicit TWToken(const FTokenPos &pos) : m_pos(pos) {}
	
	public:
		
		[[nodiscard]] virtual Bool IsEOF() const noexcept { return false; }
		
		[[nodiscard]] virtual String ToString() const noexcept = 0;
		
		[[nodiscard]] virtual String GetTypeString() const noexcept = 0;
	
	public:
		
		FTokenPos m_pos;
		
	};
	
	///
	/// 结束符
	template<class ElemT>
	class WHALE_API TWEOFToken : public TWToken<ElemT>, public FObjectCloneable<TWEOFToken<ElemT>>
	{
	public:
		
		using String = typename TWToken<ElemT>::String;
	
	public:
		
		explicit TWEOFToken(const FTokenPos &pos) : TWToken<ElemT>(pos) {}
	
	public:
		
		[[nodiscard]] Bool IsEOF() const noexcept override { return true; }
		
		[[nodiscard]]
		String ToString() const noexcept override { return GetTypeString(); }
		
		[[nodiscard]]
		String GetTypeString() const noexcept override;
		
	};
	
	template<>
	inline TWToken<CharA>::String WHALE_API
	TWEOFToken<CharA>::GetTypeString() const noexcept { return "EOF"; }
	
	template<>
	inline TWToken<CharW>::String WHALE_API
	TWEOFToken<CharW>::GetTypeString() const noexcept { return L"EOF"; }
	
	///
	/// 操作符
	template<class ElemT>
	class WHALE_API TWOperatorToken : public TWToken<ElemT>, public FObjectCloneable<TWOperatorToken<ElemT>>
	{
	public:
		
		using String = typename TWToken<ElemT>::String;
	
	public:
		
		explicit TWOperatorToken(const FTokenPos &pos, ElemT anOperator) : TWToken<ElemT>(pos),
																		   m_operator(anOperator) {}
	
	public:
		
		[[nodiscard]]
		String ToString() const noexcept override
		{
			return String{&m_operator, 1};
		}
		
		[[nodiscard]]
		String GetTypeString() const noexcept override;
	
	public:
		
		ElemT m_operator;
		
	};
	
	template<>
	inline TWToken<CharA>::String WHALE_API
	TWOperatorToken<CharA>::GetTypeString() const noexcept { return "Operator"; }
	
	template<>
	inline TWToken<CharW>::String WHALE_API
	TWOperatorToken<CharW>::GetTypeString() const noexcept { return L"Operator"; }
	
	///
	/// 标识符
	template<class ElemT>
	class WHALE_API TWIdentifierToken
		: public TWToken<ElemT>, public FObjectCloneable<TWIdentifierToken<ElemT>>
	{
	public:
		
		using String = typename TWToken<ElemT>::String;
	
	public:
		
		explicit TWIdentifierToken(const FTokenPos &pos, const String &anString) : TWToken<ElemT>(pos),
																				   m_string(anString) {}
	
	public:
		
		[[nodiscard]]
		String ToString() const noexcept override { return m_string; }
		
		[[nodiscard]]
		String GetTypeString() const noexcept override;
	
	public:
		
		String m_string;
		
	};
	
	template<>
	inline TWToken<CharA>::String WHALE_API
	TWIdentifierToken<CharA>::GetTypeString() const noexcept { return "Identifier"; }
	
	template<>
	inline TWToken<CharW>::String WHALE_API
	TWIdentifierToken<CharW>::GetTypeString() const noexcept { return L"Identifier"; }
	
	
	///
	/// 字符字面量
	template<class ElemT>
	class WHALE_API TWCharToken : public TWToken<ElemT>, public FObjectCloneable<TWCharToken<ElemT>>
	{
	public:
		
		using String = typename TWToken<ElemT>::String;
	
	public:
		
		TWCharToken() : m_char() {}
		
		explicit TWCharToken(const FTokenPos &pos, const ElemT &anChar) : TWToken<ElemT>(pos),
																		  m_char(anChar) {}
	
	public:
		
		[[nodiscard]]
		String ToString() const noexcept override { return String(&m_char, 1); }
		
		[[nodiscard]]
		String GetTypeString() const noexcept override;
	
	public:
		
		ElemT m_char;
		
	};
	
	template<>
	inline TWToken<CharA>::String WHALE_API
	TWCharToken<CharA>::GetTypeString() const noexcept { return "Char"; }
	
	template<>
	inline TWToken<CharW>::String WHALE_API
	TWCharToken<CharW>::GetTypeString() const noexcept { return L"Char"; }
	
	
	///
	/// 字符串字面量
	template<class ElemT>
	class WHALE_API TWStringToken : public TWToken<ElemT>, public FObjectCloneable<TWStringToken<ElemT>>
	{
	public:
		
		using String = typename TWToken<ElemT>::String;
	
	public:
		
		TWStringToken() : m_string() {}
		
		explicit TWStringToken(const FTokenPos &pos, const String &anString) : TWToken<ElemT>(pos),
																			   m_string(anString) {}
	
	public:
		
		[[nodiscard]]
		String ToString() const noexcept override { return m_string; }
		
		[[nodiscard]]
		String GetTypeString() const noexcept override;
	
	public:
		
		String m_string;
		
	};
	
	template<>
	inline TWToken<CharA>::String WHALE_API
	TWStringToken<CharA>::GetTypeString() const noexcept { return "String"; }
	
	template<>
	inline TWToken<CharW>::String WHALE_API
	TWStringToken<CharW>::GetTypeString() const noexcept { return L"String"; }
	
	///
	/// 数字字面量
	template<class ElemT>
	class WHALE_API TWNumberToken : public TWToken<ElemT>, public FObjectCloneable<TWNumberToken<ElemT>>
	{
	public:
		
		using String = typename TWToken<ElemT>::String;
	
	public:
		
		TWNumberToken() : m_string() {}
		
		explicit TWNumberToken(const FTokenPos &pos, const String &anString) : TWToken<ElemT>(pos),
																			   m_string(anString) {}
	
	public:
		
		[[nodiscard]]
		String ToString() const noexcept override { return m_string; }
		
		[[nodiscard]]
		String GetTypeString() const noexcept override;
	
	public:
		
		String m_string;
		
	};
	
	template<>
	inline TWToken<CharA>::String WHALE_API
	TWNumberToken<CharA>::GetTypeString() const noexcept { return "Number"; }
	
	template<>
	inline TWToken<CharW>::String WHALE_API
	TWNumberToken<CharW>::GetTypeString() const noexcept { return L"Number"; }
	#endif
	
} // Whale
