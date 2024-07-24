//
// Created by admin on 2024/7/19.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"
#include "Whale/Core/Container/TFString.hpp"
#include "Whale/Core/Stream.hpp"

#include <cstdio>
#include <functional>

namespace Whale::IO
{
	
	constexpr const CharA TagA[] = "Whale::IO";
	constexpr const CharW TagW[] = L"Whale::IO";
	
	template<class ElemT>
	int32 FileGet(FILE *file) noexcept
	{
		static_assert("Not implemented");
	}
	
	template<class ElemT>
	int32 FilePut(FILE *file, ElemT elem) noexcept
	{
		static_assert("Not implemented");
	}
	
	///
	/// 文件
	template<class ElemT>
	class WHALE_API FFileStream : public TIStream<int32, ElemT>
	{
	public:
		
		using String = Container::TFString<ElemT>;
	
	public:
		
		FFileStream() noexcept: m_file(nullptr), m_now(0), m_peek(0), m_isCloseF(false) {}
		
		///
		/// \param file 文件流
		/// \param isCloseF 是否需要关闭
		FFileStream(FILE *file, Bool isCloseF) noexcept: m_file(file), m_now(0), m_peek(0), m_isCloseF(isCloseF) {}
		
		FFileStream(const FFileStream &) = delete;
		
		~FFileStream() noexcept;
	
	public:
		
		FFileStream &operator=(const FFileStream &) = delete;
	
	public:
		
		///
		/// 关闭文件
		/// \return 是否成功
		Bool Close() noexcept;
	
	public:
		
		[[nodiscard]] Bool Good() const noexcept override { return !(IsError() || IsEOF()); }
		
		[[nodiscard]] Bool Bad() const noexcept override { return IsError() || IsEOF(); }
		
		[[nodiscard]] Bool IsOpen() const noexcept { return this->m_file != 0; }
		
		[[nodiscard]] Bool IsError() const noexcept { return ::ferror(this->m_file) != 0; }
		
		[[nodiscard]] Bool IsEOF() const noexcept { return ::feof(this->m_file) != 0; }
		
		int32 Peek() noexcept override { return GetPeek(); }
		
		int32 Read() noexcept override;
		
		FFileStream &Write(ElemT elem) noexcept override;
		
		template<class... Args>
		FFileStream &Writes(Args... args) noexcept;
		
		FFileStream &Flush() noexcept override;
		
		FFileStream &Write(const String &str) noexcept;
		
		FFileStream &WriteLine() noexcept;
		
		FFileStream &WriteLine(const String &str) noexcept;
		
		FFileStream &Read(String &str) noexcept;
		
		FFileStream &ReadTo(const std::function<Bool(int32)> &stopFunction) noexcept;
		
		FFileStream &ReadTo(String &str, const std::function<Bool(int32)> &stopFunction) noexcept;
		
		FFileStream &ReadToNewLine() noexcept;
		
		FFileStream &ReadLine(String &str) noexcept;
		
		///
		/// 清空错误
		FFileStream &ClearError() noexcept;
		
		///
		/// 清空错误
		const FFileStream &ClearError() const noexcept;
		
		///
		/// \param file 文件流
		/// \param isCloseF 是否需要关闭
		void Reset(FILE *file, Bool isCloseF)
		{
			this->m_file = file;
			this->m_now = 0;
			this->m_peek = 0;
			this->m_isCloseF = isCloseF;
			Read();
		}
	
	public:
		
		///
		/// \return 指向C流的指针
		[[nodiscard]] FILE *GetFile() const noexcept { return this->m_file; }
		
		///
		/// \return 当前字符
		[[nodiscard]] int32 GetNow() const noexcept { return m_now; }
		
		///
		/// \return 下一个字符
		[[nodiscard]] int32 GetPeek() const noexcept { return m_peek; }
		
		///
		/// \return 如果C流必须关闭，则为true。
		[[nodiscard]] Bool IsCloseF() const noexcept { return this->m_isCloseF; }
		
		///
		/// \param isCloseF 如果C流必须关闭，则为true。
		void SetIsCloseF(Bool isCloseF) noexcept { this->m_isCloseF = isCloseF; }
	
	private:
		
		FILE *m_file;
		int32 m_now;
		int32 m_peek;
		Bool m_isCloseF;
		
	};
	
	using FileStreamA = FFileStream<CharA>;
	using FileStreamW = FFileStream<CharW>;
	using FileStreamT = FFileStream<CharT>;
	
	
} // Whale

#include "IO.inl"
