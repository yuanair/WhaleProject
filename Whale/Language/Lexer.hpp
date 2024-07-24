//
// Created by admin on 2024/7/22.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"
#include "Whale/Core/Stream.hpp"
#include "Whale/Language/TILexer.hpp"

namespace Whale
{
	
	///
	/// 词法分析错误
	enum ELexerError
	{
		ELexerErrorUnknown = 0,
		ELexerErrorUnknownChar,
	};
	
	///
	/// 词法分析错误
	template<class ElemT>
	class WHALE_API TFLexerError
	{
	public:
		
		using String = Container::TFString<ElemT>;
	
	public:
		
		TFLexerError() : pos(), error(ELexerErrorUnknown), message() {}
		
		TFLexerError(const FTokenPos &pos, ELexerError error, const String &message) : pos(pos), error(error),
		                                                                               message(message) {}
	
	public:
		
		FTokenPos pos;
		
		ELexerError error;
		
		String message;
		
	};
	
	///
	/// Json词法分析器
	template<class ElemT>
	class TWLexer : public WObject, public TILexer<ElemT>
	{
	public:
		
		using StateFunctionType = TFUniquePtr<TWToken<ElemT>> (TWLexer::*)();
		
		using String = Container::TFString<ElemT>;
		
		using Error = TFLexerError<ElemT>;
	
	public:
		
		explicit TWLexer(TIStreamReader<ElemT> &streamReader) : m_streamReader(streamReader),
		                                                        m_stateFunction(&TWLexer::SpaceNextState),
		                                                        m_peek() {}
		
		~TWLexer() noexcept override {}
	
	public:
		
		[[nodiscard]] Bool IsEOF() const noexcept { return this->m_peek ? this->m_peek->IsEOF() : false; }
		
		[[nodiscard]] Bool Good() const noexcept override
		{
			return this->m_streamReader.Good();
		}
		
		[[nodiscard]] Bool Bad() const noexcept override
		{
			return this->m_streamReader.Bad();
		}
	
	public:
		
		TFUniquePtr<TWToken<ElemT>> Peek() noexcept override
		{
			return TFUniquePtr<TWToken<ElemT>>(dynamic_cast<TWToken<ElemT> *>(m_peek->Clone().Release()));
		}
		
		TFUniquePtr<TWToken<ElemT>> Read() noexcept override
		{
			TFUniquePtr<TWToken<ElemT>> result = Whale::Move(this->m_peek);
			this->m_peek = (this->*m_stateFunction)();
			return result;
		}
		
		[[nodiscard]]
		Bool IsNumberStart(int32 ch) const noexcept
		{
			return FLocale::IsDigit(ch) || '.' == ch;
		}
		
		[[nodiscard]]
		Bool IsNumberContinue(int32 ch) const noexcept
		{
			return FLocale::IsADigit(ch) || '.' == ch;
		}
		
		[[nodiscard]]
		Bool IsIdentifierStart(int32 ch) const noexcept
		{
			return FLocale::IsAlpha(ch) || '_' == ch || '@' == ch;
		}
		
		[[nodiscard]]
		Bool IsIdentifierContinue(int32 ch) const noexcept
		{
			return FLocale::IsADigit(ch) || '_' == ch || '@' == ch;
		}
		
		void AppendError(ELexerError error, const String &message) noexcept
		{
			this->m_errors.Append(Error(m_pos, error, message));
		}
		
		template<typename T, typename ... Args>
		TFUniquePtr<T> MakeToken(Args &&... args) noexcept
		{
			return MakeUnique<T>(m_pos, args...);
		}
	
	public:
		
		[[nodiscard]] const FTokenPos &GetPos() const noexcept { return m_pos; }
		
		[[nodiscard]] TIStreamReader<ElemT> &GetInputStream() const noexcept { return m_streamReader; }
		
		[[nodiscard]] StateFunctionType GetStateFunction() const noexcept { return m_stateFunction; }
		
		[[nodiscard]] const Container::TFArray<Error> &GetErrors() const noexcept { return m_errors; }
	
	private:
		
		void NextChar() noexcept
		{
			GetInputStream().Read();
			m_pos.column++;
		}
		
		TFUniquePtr<TWToken<ElemT>> SpaceNextState();
		
		TFUniquePtr<TWToken<ElemT>> IdentifierNextState();
		
		TFUniquePtr<TWToken<ElemT>> NumberNextState();
	
	private:
		
		FTokenPos m_pos;
		
		TIStreamReader<ElemT> &m_streamReader;
		
		StateFunctionType m_stateFunction;
		
		TFUniquePtr<TWToken<ElemT>> m_peek;
		
		Container::TFArray<Error> m_errors;
		
	};
	
	template<class ElemT>
	TFUniquePtr<TWToken<ElemT>> TWLexer<ElemT>::SpaceNextState()
	{
		while (true)
		{
			ElemT elem = GetInputStream().Peek();
			if (GetInputStream().Bad())
			{
				return MakeToken<TWEOFToken<ElemT>>();
			}
			else if (FLocale::IsSpaceIncludeNull(elem))
			{
			
			}
			else if (IsNumberStart(elem))
			{
				m_stateFunction = &TWLexer::NumberNextState;
				return nullptr;
			}
			else if (IsIdentifierStart(elem))
			{
				m_stateFunction = &TWLexer::IdentifierNextState;
				return nullptr;
			}
			else
			{
				AppendError(ELexerErrorUnknownChar, FLocale::AToString<String>("unknown char", "UTF-8"));
			}
			NextChar();
		}
	}
	
	template<class ElemT>
	TFUniquePtr<TWToken<ElemT>> TWLexer<ElemT>::IdentifierNextState()
	{
		String buffer;
		while (true)
		{
			ElemT elem = GetInputStream().Peek();
			if (GetInputStream().Bad())
			{
				break;
			}
			else if (FLocale::IsSpaceIncludeNull(elem))
			{
				break;
			}
			else if (IsIdentifierContinue(elem))
			{
				buffer.Append(elem);
			}
			else
			{
				break;
			}
			NextChar();
		}
		m_stateFunction = &TWLexer::SpaceNextState;
		return MakeToken<TWIdentifierToken<ElemT>>(buffer);
	}
	
	template<class ElemT>
	TFUniquePtr<TWToken<ElemT>> TWLexer<ElemT>::NumberNextState()
	{
		String buffer;
		while (true)
		{
			ElemT elem = GetInputStream().Peek();
			if (GetInputStream().Bad())
			{
				break;
			}
			else if (FLocale::IsSpaceIncludeNull(elem))
			{
				break;
			}
			else if (IsNumberContinue(elem))
			{
				buffer.Append(elem);
			}
			else
			{
			
			}
			NextChar();
		}
		m_stateFunction = &TWLexer::SpaceNextState;
		return MakeToken<TWLiteralToken<ElemT>>(buffer);
	}
	
	
}
