#include "FDebug.hpp"

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
		FDebug::LogError(LogTagA, "FileClose Failed!");
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
		ElemT result{};
		if (!FileGet(result, this->myFile))
			throw FIOException("FFileStream<ElemT>::Peek() failed");
		if (!FileUnGet(result, this->myFile))
			throw FIOException("FFileStream<ElemT>::Peek() failed");
		return result;
	}
	
	template<class ElemT>
	ElemT FFileStream<ElemT>::Get()
	{
		ElemT result{};
		if (FileGet(result, this->myFile)) return result;
		throw FIOException("FFileStream<ElemT>::Get() failed");
	}
	
	template<class ElemT>
	ElemT FFileStream<ElemT>::UnGet()
	{
		ElemT result{};
		if (FileUnGet(result, this->myFile)) return result;
		return this->myChar;
	}
	
	template<class ElemT>
	TIOutputStream<ElemT> &FFileStream<ElemT>::Put(ElemT elem)
	{
		if (FilePut(elem, this->myFile)) return *this;
		throw FIOException("FFileStream<ElemT>::Write(ElemT) failed");
	}
	
	template<class ElemT>
	TIOutputStream<ElemT> &FFileStream<ElemT>::Write(const String &str)
	{
		for (auto ch: str)
		{
			if (!FilePut(ch, this->myFile))
			{
				throw FIOException("FFileStream<ElemT>::Write(FFileStream::String) failed");
			}
		}
		return *this;
	}
	
	template<class ElemT>
	TIOutputStream<ElemT> &FFileStream<ElemT>::WriteLine(const FFileStream::String &str)
	{
		for (auto ch: str)
		{
			if (!FilePut(ch, this->myFile))
			{
				throw FIOException("FFileStream<ElemT>::Write(FFileStream::String) failed");
			}
		}
		if (!FilePuts(this->myFile, WHALE_NEWLINE))
		{
			throw FIOException("FFileStream<ElemT>::Write(FFileStream::String) failed");
		}
		return *this;
	}
	
	template<class ElemT>
	TIOutputStream<ElemT> &
	FFileStream<ElemT>::ReadTo(FFileStream::String &str, const std::function<Bool(ElemT)> &stopFunction)
	{
		ElemT elem{};
		while (FileGet(elem, this->myFile))
		{
			if (stopFunction(elem)) return *this;
			str.Append(elem);
		}
		throw FIOException("FFileStream<ElemT>::ReadTo(FFileStream::String &) failed");
	}
	
	template<class ElemT>
	template<class... Args>
	TIOutputStream<ElemT> &FFileStream<ElemT>::Puts(ElemT elem, Args... args)
	{
		if (FilePuts(this->myFile, args...)) return *this;
		throw FIOException("FFileStream<ElemT>::Write(ElemT) failed");
	}
	
	template<class ElemT>
	TIOutputStream<ElemT> &FFileStream<ElemT>::Flush()
	{
		throw FIOException("FFileStream<ElemT>::Flush() failed");
	}
	
}