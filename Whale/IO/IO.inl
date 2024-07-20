#include "Whale/Core/FDebug.hpp"
#include "Whale/Core/FLocale.hpp"

namespace Whale::IO
{
	template<class ElemT>
	errno_t FileOpen(FILE **pFile, const ElemT *fileName, const ElemT *openMode) noexcept
	{
		return ::fopen_s(pFile, fileName, openMode);
	}
	
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
		if (!isCloseF || Close()) return;
		FDebug::LogError(TagA, "FileClose Failed!");
	}
	
	template<class ElemT>
	Bool FFileStream<ElemT>::Close() noexcept
	{
		Bool result = FileClose(this->myFile);
		this->myFile = nullptr;
		return result;
	}
	
	template<class ElemT>
	ElemT FFileStream<ElemT>::Peek()
	{
		return this->myChar;
	}
	
	template<class ElemT>
	Bool FFileStream<ElemT>::Get(ElemT &elem)
	{
		elem = this->myChar;
		return FileGet(this->myChar, this->myFile);
	}
	
	template<class ElemT>
	Bool FFileStream<ElemT>::UnGet(ElemT &elem)
	{
		elem = this->myChar;
		return FileUnGet(this->myChar, this->myFile);
	}
	
	template<class ElemT>
	Bool FFileStream<ElemT>::Put(ElemT elem)
	{
		return FilePut(elem, this->myFile);
	}
	
	template<class ElemT>
	template<class... Args>
	Bool FFileStream<ElemT>::Puts(ElemT elem, Args... args)
	{
		return FilePuts(this->myFile, elem, args...);
	}
	
	template<class ElemT>
	Bool FFileStream<ElemT>::Flush()
	{
		return ::fflush(this->myFile);
	}
	
	template<class ElemT>
	Bool FFileStream<ElemT>::ReadToNewLine()
	{
		ElemT elem;
		while (true)
		{
			if (FLocale::IsNewLine(Peek()) || Peek() == 0) break;
			if (!Get(elem)) throw FIOException("FFileStream<ElemT>::ReadToNewLine() failed");
		}
	}
	
	template<class ElemT>
	Bool FFileStream<ElemT>::Write(const String &str)
	{
		for (auto ch: str)
		{
			if (!Put(ch))
				throw FIOException("FFileStream<ElemT>::Write(FFileStream::String) failed");
		}
		return true;
	}
	
	template<class ElemT>
	Bool FFileStream<ElemT>::WriteLine(const FFileStream::String &str)
	{
		for (auto ch: str)
		{
			if (!Put(ch))
				throw FIOException("FFileStream<ElemT>::Write(FFileStream::String) failed");
		}
		if (!Puts(WHALE_NEWLINE))
			throw FIOException("FFileStream<ElemT>::Write(FFileStream::String) failed");
		
		return true;
	}
	
	template<class ElemT>
	Bool FFileStream<ElemT>::Read(FFileStream::String &str)
	{
		ElemT elem{};
		while (FLocale::IsSpace(Peek()) || Peek() == 0)
		{
			if (!Get(elem)) throw FIOException("FFileStream<ElemT>::Read(FFileStream::String &) failed");
		}
		while (true)
		{
			if (!Get(elem)) throw FIOException("FFileStream<ElemT>::Read(FFileStream::String &) failed");
			str.Append(elem);
			if (FLocale::IsSpace(Peek())) break;
		}
		if (FLocale::IsNewLine(Peek())) return true;
		while (true)
		{
			if (!Get(elem)) throw FIOException("FFileStream<ElemT>::Read(FFileStream::String &) failed");
			if (!FLocale::IsSpace(Peek()) || FLocale::IsNewLine(Peek())) break;
		}
		return true;
	}
	
	template<class ElemT>
	Bool FFileStream<ElemT>::ReadTo(const std::function<Bool(ElemT)> &stopFunction)
	{
		ElemT elem{};
		while (true)
		{
			if (!Get(elem)) throw FIOException("FFileStream<ElemT>::ReadTo(FFileStream::String &) failed");
			if (stopFunction(elem)) return true;
		}
	}
	
	template<class ElemT>
	Bool FFileStream<ElemT>::ReadTo(FFileStream::String &str, const std::function<Bool(ElemT)> &stopFunction)
	{
		ElemT elem{};
		while (true)
		{
			if (!Get(elem))throw FIOException("FFileStream<ElemT>::ReadTo(FFileStream::String &) failed");
			if (stopFunction(elem)) return true;
			str.Append(elem);
		}
	}
	
	template<class ElemT>
	Bool FFileStream<ElemT>::ReadLine(FFileStream::String &str)
	{
		return ReadTo(str, [](ElemT elem) -> Bool { return FLocale::IsNewLine(elem); });
	}
	
}