#include "Whale/Core/FDebug.hpp"
#include "Whale/Core/FLocale.hpp"

namespace Whale::IO
{
	
	template<class ElemT>
	Bool FileGet(ElemT &elem, FILE *file) noexcept
	{
		return ::fread(&elem, sizeof(ElemT), 1, file) == 1;
	}
	
	template<>
	inline Bool FileGet(CharA &elem, FILE *file) noexcept
	{
		int meta;
		if ((meta = ::fgetc(file)) == EOF)
		{
			return false;
		}
		else
		{
			elem = static_cast<CharA>(meta);
			return true;
		}
	}
	
	template<>
	inline Bool FileGet(CharW &elem, FILE *file) noexcept
	{
		wint_t meta;
		if ((meta = ::fgetwc(file)) == WEOF)
		{
			return false;
		}
		else
		{
			elem = static_cast<CharW>(meta);
			return true;
		}
	}
	
	template<class ElemT>
	Bool FilePut(ElemT elem, FILE *file) noexcept
	{
		return ::fwrite(&elem, 1, sizeof(ElemT), file) == sizeof(ElemT);
	}
	
	template<>
	inline Bool FilePut(char elem, FILE *file) noexcept
	{
		return ::fputc(elem, file) != EOF;
	}
	
	template<>
	inline Bool FilePut(wchar_t elem, FILE *file) noexcept
	{
		return ::fputwc(elem, file) != WEOF;
	}
	
	template<>
	inline Bool FileUnGet(const char &elem, FILE *file) noexcept
	{
		return ::ungetc(static_cast<unsigned char>(elem), file) != EOF;
	}
	
	template<>
	inline Bool FileUnGet(const signed char &elem, FILE *file) noexcept
	{
		return ::ungetc(static_cast<unsigned char>(elem), file) != EOF;
	}
	
	template<>
	inline Bool FileUnGet(const unsigned char &elem, FILE *file) noexcept
	{
		return ::ungetc(elem, file) != EOF;
	}
	
	template<>
	inline Bool FileUnGet(const wchar_t &elem, FILE *file) noexcept
	{
		return ::ungetwc(elem, file) != WEOF;
	}
	
	inline Bool FileClose(FILE *file) noexcept
	{
		return ::fclose(file) != EOF;
	}
	
	template<class ElemT>
	FFileStream<ElemT>::~FFileStream() noexcept
	{
		Close();
	}
	
	template<class ElemT>
	void FFileStream<ElemT>::Close() noexcept
	{
		Bool result = !m_isCloseF || FileClose(this->m_file);
		this->m_file = nullptr;
		this->m_state = result ? EFileStateClosed : EFileStateFileError;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::Peek(ElemT &elem) noexcept
	{
		elem = this->m_peek;
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::Get(ElemT &elem) noexcept
	{
		elem = this->m_peek;
		if (!FileGet(this->m_peek, this->m_file))this->m_state = EFileStateFileEOF;
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::UnGet(ElemT &elem) noexcept
	{
		elem = this->m_peek;
		if (!FileUnGet(this->m_peek, this->m_file))this->m_state = EFileStateFileError;
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::Put(ElemT elem) noexcept
	{
		if (!FilePut(elem, this->m_file))this->m_state = EFileStateFileError;
		return *this;
	}
	
	template<class ElemT>
	template<class... Args>
	FFileStream<ElemT> &FFileStream<ElemT>::Puts(ElemT elem, Args... args) noexcept
	{
		if (!FilePuts(this->m_file, elem, args...))this->m_state = EFileStateFileError;
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::Flush() noexcept
	{
		if (!::fflush(this->m_file))this->m_state = EFileStateFileError;
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::ReadToNewLine() noexcept
	{
		ElemT elem;
		while (true)
		{
			if (FLocale::IsNewLine(this->m_peek) || this->m_peek == 0 || !Get(elem)) break;
		}
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::Write(const String &str) noexcept
	{
		for (auto ch: str)
		{
			if (!Put(ch)) break;
		}
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::WriteLine(const FFileStream::String &str) noexcept
	{
		for (auto ch: str)
		{
			if (!Put(ch)) return *this;
		}
		return Puts(WHALE_NEWLINE);
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::Read(FFileStream::String &str) noexcept
	{
		ElemT elem{};
		while (FLocale::IsSpace(this->m_peek) || this->m_peek == 0)
		{
			if (!Get(elem)) return *this;
		}
		while (true)
		{
			if (!Get(elem)) return *this;
			str.Append(elem);
			if (FLocale::IsSpace(this->m_peek)) break;
		}
		if (FLocale::IsNewLine(this->m_peek)) return *this;
		while (true)
		{
			if (!Get(elem)) return *this;
			if (!FLocale::IsSpace(this->m_peek) || FLocale::IsNewLine(this->m_peek)) break;
		}
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::ReadTo(const std::function<Bool(ElemT)> &stopFunction) noexcept
	{
		ElemT elem{};
		while (true)
		{
			if (!Get(elem) || stopFunction(elem)) break;
		}
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &
	FFileStream<ElemT>::ReadTo(FFileStream::String &str, const std::function<Bool(ElemT)> &stopFunction) noexcept
	{
		ElemT elem{};
		while (true)
		{
			if (!Get(elem) || stopFunction(elem)) break;
			str.Append(elem);
		}
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::ReadLine(FFileStream::String &str) noexcept
	{
		return ReadTo(str, [](ElemT elem) -> Bool { return FLocale::IsNewLine(elem); });
	}
	
}