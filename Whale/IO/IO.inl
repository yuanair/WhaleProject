#include "Whale/Core/FDebug.hpp"
#include "Whale/Core/FLocale.hpp"

namespace Whale::IO
{
	
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
	Bool FFileStream<ElemT>::Close() noexcept
	{
		Bool result = true;
		if (m_file == nullptr) return true;
		if (m_isCloseF) { result = ::fclose(this->m_file) == 0; }
		this->m_file = nullptr;
		return result;
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
		return *this;
	}
	
	template<class ElemT>
	template<class... Args>
	FFileStream<ElemT> &FFileStream<ElemT>::Writes(Args... args) noexcept
	{
		(... && FilePut(this->m_file, args));
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::Flush() noexcept
	{
		::fflush(this->m_file);
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::ReadToNewLine() noexcept
	{
		while (true)
		{
			if (Bad()) return *this;
			if (FLocale::IsNewLine(this->m_peek)) break;
			Read();
		}
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
			if (!FLocale::IsSpaceIncludeNull(this->m_peek)) break;
			Read();
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
			if (stopFunction(this->m_peek)) break;
			Read();
		}
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &
	FFileStream<ElemT>::ReadTo(FFileStream::String &str, const std::function<Bool(int32)> &stopFunction) noexcept
	{
		while (true)
		{
			if (Bad()) return *this;
			if (stopFunction(this->m_peek)) break;
			str.Append((ElemT) this->m_peek);
			Read();
		}
		return *this;
	}
	
	template<class ElemT>
	FFileStream<ElemT> &FFileStream<ElemT>::ReadLine(FFileStream::String &str) noexcept
	{
		return ReadTo(str, [](int32 elem) -> Bool { return FLocale::IsNewLine(elem); });
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