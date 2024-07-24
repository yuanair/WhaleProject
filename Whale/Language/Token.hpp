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
	/// 字面量
	template<class ElemT>
	class WHALE_API TWLiteralToken : public TWToken<ElemT>, public FObjectCloneable<TWLiteralToken<ElemT>>
	{
	public:
		
		using String = typename TWToken<ElemT>::String;
	
	public:
		
		TWLiteralToken() : m_string() {}
		
		explicit TWLiteralToken(const FTokenPos &pos, const String &anString) : TWToken<ElemT>(pos),
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
	TWLiteralToken<CharA>::GetTypeString() const noexcept { return "Literal"; }
	
	template<>
	inline TWToken<CharW>::String WHALE_API
	TWLiteralToken<CharW>::GetTypeString() const noexcept { return L"Literal"; }
	
	
} // Whale
