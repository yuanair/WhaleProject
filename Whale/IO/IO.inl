#include "Whale/Core/FDebug.hpp"
#include "Whale/Core/FLocale.hpp"

namespace Whale::IO
{
	
	#if WHALE_COMPILER_TYPE == WHALE_COMPILER_TYPE_MSVC
	
	template<>
	inline void WHALE_API FileOpen(FILE **file, const CharA* fileName, const CharA* mode) noexcept
	{
		::fopen_s(file, fileName, mode);
	}
	
	template<>
	inline void WHALE_API FileOpen(FILE **file, const CharW* fileName, const CharW* mode) noexcept
	{
		::_wfopen_s(file, fileName, mode);
	}
	
	#else
	
	template<>
	inline void WHALE_API FileOpen(FILE **file, const CharA* fileName, const CharA* mode) noexcept
	{
		*file = ::fopen(file, fileName, mode);
	}
	
	template<>
	inline void WHALE_API FileOpen(FILE **file, const CharW* fileName, const CharW* mode) noexcept
	{
		*file = ::_wfopen_s(file, fileName, mode);
	}
	
	#endif
	
	template<>
	inline int32 WHALE_API FileGet<CharA>(FILE *file) noexcept
	{
		return ::fgetc(file);
	}
	
	template<>
	inline int32 WHALE_API FileGet<CharW>(FILE *file) noexcept
	{
		return ::fgetwc(file);
	}
	
	template<>
	inline int32 WHALE_API FilePut(FILE *file, CharA elem) noexcept
	{
		return ::fputc(elem, file);
	}
	
	template<>
	inline int32 WHALE_API FilePut(FILE *file, CharW elem) noexcept
	{
		return ::fputwc(elem, file);
	}
	
	template<class ElemT>
	FFileStream<ElemT>::~FFileStream() noexcept
	{
		Close();
	}
	
	template<class ElemT>
	FFileStream<ElemT>& FFileStream<ElemT>::Open(const String& fileName, const String& mode, Bool isCloseF, Bool isFlushNewline) noexcept
	{
		Close();
		FileOpen(&this->m_file, fileName.CStr(), mode.CStr());
		this->m_peek = 0;
		this->m_now = 0;
		this->m_isCloseF = isCloseF;
		this->m_isFlushNewline = isFlushNewline;
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT>& FFileStream<ElemT>::Reset(FILE *file, Bool isCloseF, Bool isFlushNewline) noexcept
	{
		Close();
		this->m_file = file;
		this->m_now = 0;
		this->m_peek = 0;
		this->m_isCloseF = isCloseF;
		this->m_isFlushNewline = isFlushNewline;
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT>& FFileStream<ElemT>::Close() noexcept
	{
		if (m_file && m_isCloseF) { ::fclose(this->m_file); }
		this->m_file = nullptr;
		return *this;
	}
	
	template<class ElemT>
	int32 FFileStream<ElemT>::Read() noexcept
	{
		this->m_now = this->m_peek;
		this->m_peek = FileGet<ElemT>(this->m_file);
		return this->m_now;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::Write(ElemT elem) noexcept
	{
		FilePut(this->m_file, elem);
		if (m_isFlushNewline && FLocale::IsNewLine(elem)) Flush();
		return *this;
	}
	
	template<class ElemT>
	template<class... Args>
	FFileStream<ElemT> &FFileStream<ElemT>::Writes(Args... args) noexcept
	{
		(... && Write(args));
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::Flush() noexcept
	{
		::fflush(this->m_file);
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::Write(const String &str) noexcept
	{
		for (ElemT ch: str)
		{
			if (Bad()) return *this;
			Write(ch);
		}
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::WriteLine() noexcept
	{
		return Writes(WHALE_NEWLINE);
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::WriteLine(const FFileStream::String &str) noexcept
	{
		for (ElemT ch: str)
		{
			if (Bad()) return *this;
			Write(ch);
		}
		return Writes(WHALE_NEWLINE);
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::Read(FFileStream::String &str) noexcept
	{
		while (true)
		{
			if (Bad()) return *this;
			Read();
			if (!FLocale::IsSpaceIncludeNull(this->m_peek)) break;
		}
		while (true)
		{
			if (Bad()) return *this;
			if (FLocale::IsSpace(this->m_peek)) break;
			str.Append(this->m_peek);
			Read();
		}
		if (FLocale::IsNewLine(this->m_peek)) return *this;
		while (true)
		{
			if (Bad()) return *this;
			if (!FLocale::IsSpace(this->m_peek) || FLocale::IsNewLine(this->m_peek)) break;
			Read();
		}
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::ReadTo(const std::function<Bool(int32)> &stopFunction) noexcept
	{
		while (true)
		{
			if (Bad()) return *this;
			Read();
			if ('\0' != this->m_peek) break;
		}
		while (true)
		{
			if (Bad()) return *this;
			if (stopFunction(this->m_peek)) break;
			Read();
		}
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &
	FFileStream<ElemT>::ReadTo(const std::function<Bool(int32)> &stopFunction, String &str) noexcept
	{
		while (true)
		{
			if (Bad()) return *this;
			Read();
			if ('\0' != this->m_peek) break;
		}
		while (true)
		{
			if (Bad()) return *this;
			if (stopFunction(this->m_peek)) break;
			str.Append(this->m_peek);
			Read();
		}
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::ReadToBack(const std::function<Bool(int32)> &stopFunction) noexcept
	{
		while (true)
		{
			if (Bad()) return *this;
			Read();
			if ('\0' != this->m_peek) break;
		}
		while (true)
		{
			if (Bad()) return *this;
			if (stopFunction(this->m_peek)) break;
			Read();
		}
		Read();
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &
	FFileStream<ElemT>::ReadToBack(const std::function<Bool(int32)> &stopFunction, String &str) noexcept
	{
		while (true)
		{
			if (Bad()) return *this;
			Read();
			if ('\0' != this->m_peek) break;
		}
		while (true)
		{
			if (Bad()) return *this;
			if (stopFunction(this->m_peek)) break;
			str.Append(this->m_peek);
			Read();
		}
		Read();
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::ReadToNewLine() noexcept
	{
		return ReadTo([](int32 elem) -> Bool { return FLocale::IsNewLine(elem) || FLocale::IsEOF(elem); });
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::ReadLine(FFileStream::String &str) noexcept
	{
		return ReadTo([](int32 elem) -> Bool { return FLocale::IsNewLine(elem) || FLocale::IsEOF(elem); }, str);
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::ClearError() noexcept
	{
		::clearerr(this->m_file);
		return *this;
	}
	
	template<class ElemT>
	const FFileStream<ElemT> &FFileStream<ElemT>::ClearError() const noexcept
	{
		::clearerr(this->m_file);
		return *this;
	}
	
}