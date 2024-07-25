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
		ELexerErrorMissingClosingQuote,
		ELexerErrorIncorrectNumberOfCharConstants
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
		
		explicit TWLexer(TIStreamReader<ElemT> &streamReader)
			: m_pos(1, 0),
			  m_streamReader(streamReader),
			  m_stateFunction(&TWLexer::SpaceNextState),
			  m_peek(),
			  m_errors()
		{
			Read();
		}
		
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
			return MakeUnique<TWToken<ElemT>>(*m_peek);
		}
		
		TFUniquePtr<TWToken<ElemT>> Read() noexcept override
		{
			TFUniquePtr<TWToken<ElemT>> result = Whale::Move(this->m_peek);
			while (!(this->m_peek = (this->*m_stateFunction)()));
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
			if (FLocale::IsNewLine(GetInputStream().Read()))
			{
				m_pos.line++;
				m_pos.column = 0;
			}
			else
			{
				m_pos.column++;
			}
		}
		
		TFUniquePtr<TWToken<ElemT>> SpaceNextState();
		
		TFUniquePtr<TWToken<ElemT>> IdentifierNextState();
		
		TFUniquePtr<TWToken<ElemT>> NumberNextState();
		
		TFUniquePtr<TWToken<ElemT>> CharNextState();
		
		TFUniquePtr<TWToken<ElemT>> StringNextState();
	
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
				return MakeToken<TWToken<ElemT>>(ETokenTypeEOF, String());
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
			else if ('\'' == elem)
			{
				m_stateFunction = &TWLexer::CharNextState;
				NextChar();
				return nullptr;
			}
			else if ('"' == elem)
			{
				m_stateFunction = &TWLexer::StringNextState;
				NextChar();
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
		return MakeToken<TWToken<ElemT>>(ETokenTypeIdentifier, buffer);
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
				break;
			}
			NextChar();
		}
		m_stateFunction = &TWLexer::SpaceNextState;
		return MakeToken<TWToken<ElemT>>(ETokenTypeNumber, buffer);
	}
	
	template<class ElemT>
	TFUniquePtr<TWToken<ElemT>> TWLexer<ElemT>::CharNextState()
	{
		String buffer;
		while (true)
		{
			ElemT elem = GetInputStream().Peek();
			if (GetInputStream().Bad() || FLocale::IsNewLine(elem))
			{
				AppendError(
					ELexerErrorMissingClosingQuote, FLocale::AToString<String>("missing closing quote ['] ", "UTF-8"));
				break;
			}
			else if ('\\' == elem)
			{
				NextChar();
				elem = GetInputStream().Peek();
				if (GetInputStream().Bad())
				{
					AppendError(
						ELexerErrorMissingClosingQuote,
						FLocale::AToString<String>("missing closing quote ['] ", "UTF-8"));
					break;
				}
				buffer.Append(FLocale::Escape(elem));
			}
			else if ('\'' == elem)
			{
				NextChar();
				break;
			}
			else
			{
				buffer.Append(elem);
			}
			NextChar();
		}
		if (buffer.GetLength() != 1)
		{
			AppendError(
				ELexerErrorIncorrectNumberOfCharConstants,
				FLocale::AToString<String>("The number of characters must be one", "UTF-8"));
		}
		m_stateFunction = &TWLexer::SpaceNextState;
		return MakeToken<TWToken<ElemT>>(ETokenTypeChar, buffer);
	}
	
	template<class ElemT>
	TFUniquePtr<TWToken<ElemT>> TWLexer<ElemT>::StringNextState()
	{
		String buffer;
		while (true)
		{
			ElemT elem = GetInputStream().Peek();
			if (GetInputStream().Bad() || FLocale::IsNewLine(elem))
			{
				AppendError(
					ELexerErrorMissingClosingQuote, FLocale::AToString<String>("missing closing quote [\"] ", "UTF-8"));
				break;
			}
			else if ('\\' == elem)
			{
				NextChar();
				elem = GetInputStream().Peek();
				if (GetInputStream().Bad())
				{
					AppendError(
						ELexerErrorMissingClosingQuote,
						FLocale::AToString<String>("missing closing quote [\"] ", "UTF-8"));
					break;
				}
				buffer.Append(FLocale::Escape(elem));
			}
			else if ('"' == elem)
			{
				NextChar();
				break;
			}
			else
			{
				buffer.Append(elem);
			}
			NextChar();
		}
		m_stateFunction = &TWLexer::SpaceNextState;
		return MakeToken<TWToken<ElemT>>(ETokenTypeString, buffer);
	}
	
	
}
