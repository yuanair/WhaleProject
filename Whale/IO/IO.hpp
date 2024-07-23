//
// Created by admin on 2024/7/19.
//

#pragma once

#include "Whale/Core/Container/TFString.hpp"
#include "Whale/Core/Stream.hpp"

#include <cstdio>
#include <functional>

namespace Whale::IO
{
	
	constexpr const CharA TagA[] = "Whale::IO";
	constexpr const CharW TagW[] = L"Whale::IO";
	
	template<class ElemT>
	Bool FileGet(ElemT &elem, FILE *file) noexcept;
	
	template<class ElemT>
	Bool FilePut(ElemT elem, FILE *file) noexcept;
	
	template<class... Args>
	Bool FilePuts(FILE *file, Args... args) noexcept
	{
		return (... && FilePut(args, file));
	}
	
	template<class ElemT>
	Bool FileUnGet(const ElemT &elem, FILE *file) noexcept = delete;
	
	inline Bool FileClose(FILE *file) noexcept;
	
	///
	/// 文件状态
	enum EFileState
	{
		EFileStateClosed = 0,
		EFileStateOpened = 1,
		EFileStateFileNoFound = 2,
		EFileStateFileError = 3,
		EFileStateFileEOF = 4
	};
	
	///
	/// 文件
	template<class ElemT>
	class WHALE_API FFileStream : public TIStream<ElemT>
	{
	public:
		
		using String = TIStream<ElemT>::String;
	
	public:
		
		FFileStream() noexcept: m_file(nullptr), m_isCloseF(false), m_peek(0), m_state(EFileStateClosed) {}
		
		FFileStream(FILE *file, Bool isCloseF) noexcept: m_file(file), m_isCloseF(isCloseF), m_peek(0),
		                                                 m_state(EFileStateOpened) {}
		
		FFileStream(const FFileStream &) = delete;
		
		~FFileStream() noexcept;
	
	public:
		
		FFileStream &operator=(const FFileStream &) = delete;
	
	public:
		
		///
		/// 关闭文件
		void Close() noexcept;
	
	public:
		
		[[nodiscard]] Bool Good() const noexcept override { return this->m_state <= EFileStateOpened; }
		
		[[nodiscard]] Bool Bad() const noexcept override { return this->m_state > EFileStateOpened; }
		
		FFileStream &Peek(ElemT &elem) noexcept override;
		
		FFileStream &Get(ElemT &elem) noexcept override;
		
		FFileStream &UnGet(ElemT &elem) noexcept override;
		
		FFileStream &Put(ElemT elem) noexcept override;
		
		template<class... Args>
		FFileStream &Puts(ElemT elem, Args... args) noexcept;
		
		FFileStream &Flush() noexcept override;
		
		FFileStream &ReadToNewLine() noexcept;
		
		FFileStream &Write(const String &str) noexcept;
		
		FFileStream &WriteLine(const String &str) noexcept;
		
		FFileStream &Read(String &str) noexcept;
		
		FFileStream &ReadTo(const std::function<Bool(ElemT)> &stopFunction) noexcept;
		
		FFileStream &ReadTo(String &str, const std::function<Bool(ElemT)> &stopFunction) noexcept;
		
		FFileStream &ReadLine(String &str) noexcept;
	
	
	public:
		
		///
		/// \return 指向C流的指针
		[[nodiscard]] FILE *GetFile() const noexcept { return this->m_file; }
		
		///
		/// \return 下一个字符
		[[nodiscard]] ElemT GetPeek() const noexcept { return m_peek; }
		
		///
		/// \return 如果C流必须关闭，则为true。
		[[nodiscard]] Bool IsCloseF() const noexcept { return this->m_isCloseF; }
		
		///
		/// \return 文件状态
		[[nodiscard]] EFileState GetState() const noexcept { return this->m_state; }
	
	private:
		
		FILE *m_file;
		ElemT m_peek;
		Bool m_isCloseF;
		EFileState m_state;
		
	};
	
	using FileStreamA = FFileStream<CharA>;
	using FileStreamW = FFileStream<CharW>;
	using FileStreamT = FFileStream<CharT>;
	
	
} // Whale

#include "IO.inl"
