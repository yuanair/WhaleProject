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
	/// 符号
	template<class ElemT>
	class WHALE_API TWToken : public WObject
	{
	public:
		
		using String = Container::TFString<ElemT>;
	
	public:
		
		[[nodiscard]] virtual String ToString() const noexcept = 0;
		
		[[nodiscard]] virtual String GetTypeString() const noexcept = 0;
		
	};
	
	///
	/// 操作符
	template<class ElemT>
	class WHALE_API TWOperatorToken : public TWToken<ElemT>
	{
	public:
		
		using String = typename TWToken<ElemT>::String;
	
	public:
		
		explicit TWOperatorToken(ElemT anOperator) : m_operator(anOperator) {}
	
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
	class WHALE_API TWIdentifierToken : public TWToken<ElemT>
	{
	public:
		
		using String = typename TWToken<ElemT>::String;
	
	public:
		
		explicit TWIdentifierToken(const String &anString) : m_string(anString) {}
	
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
	class WHALE_API TWLiteralToken : public TWToken<ElemT>
	{
	public:
		
		using String = typename TWToken<ElemT>::String;
	
	public:
		
		explicit TWLiteralToken(const String &anString) : m_string(anString) {}
	
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
