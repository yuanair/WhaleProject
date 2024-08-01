//
// Created by admin on 2024/7/19.
//

#pragma once

#include "TypeDef.hpp"
#include "Container/TFString.hpp"
#include "Stream.hpp"
#include "TFFunction.hpp"

#include <cstdio>

namespace Whale::IO
{
	
	constexpr const CharA TagA[] = "Whale::IO";
	constexpr const CharW TagW[] = L"Whale::IO";
	
	template<class ElemT>
	void FileOpen(FILE **file, ElemT fileName, ElemT mode) noexcept
	{
		static_assert("Not implemented");
	}
	
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
		/// \param fileName 文件名
		/// \param mode 打开模式
		/// \param isCloseF 是否需要关闭
		/// \param isFlushNewline 换行是否需要刷新
		FFileStream(const String& fileName, const String& mode, Bool isCloseF = true, Bool isFlushNewline = true) noexcept { Open(fileName, mode, isCloseF, isFlushNewline);}
		
		///
		/// \param file 文件流
		/// \param isCloseF 是否需要关闭
		/// \param isFlushNewline 换行是否需要刷新
		FFileStream(FILE *file, Bool isCloseF, Bool isFlushNewline = true) noexcept { Reset(file, isCloseF, isFlushNewline); }
		
		FFileStream(const FFileStream &) = delete;
		
		~FFileStream() noexcept;
	
	public:
		
		FFileStream &operator=(const FFileStream &) = delete;
	
	public:
		
		/// 打开文件
		/// \param fileName 文件名
		/// \param mode 打开模式
		/// \param isCloseF 是否需要关闭
		/// \param isFlushNewline 换行是否需要刷新
		FFileStream& Open(const String& fileName, const String& mode, Bool isCloseF = true, Bool isFlushNewline = true) noexcept;
		
		///
		/// \param file 文件流
		/// \param isCloseF 是否需要关闭
		/// \param isFlushNewline 换行是否需要刷新
		FFileStream& Reset(FILE *file, Bool isCloseF, Bool isFlushNewline = true) noexcept;
		
		///
		/// 关闭文件
		/// \return 是否成功
		FFileStream& Close() noexcept;
		
		[[nodiscard]] Bool IsOpen() const noexcept { return this->m_file != 0; }
		
		[[nodiscard]] Bool IsError() const noexcept { return ::ferror(this->m_file) != 0; }
		
		[[nodiscard]] Bool IsEOF() const noexcept { return ::feof(this->m_file) != 0; }
		
		template<class... Args>
		FFileStream &Writes(Args... args) noexcept;
		
		FFileStream &Write(const String &str) noexcept;
		
		FFileStream &WriteLine() noexcept;
		
		FFileStream &WriteLine(const String &str) noexcept;
		
		FFileStream &Read(String &str) noexcept;
		
		FFileStream &ReadTo(const TFFunction<Bool, int32> &stopFunction) noexcept;
		
		FFileStream &ReadTo(const TFFunction<Bool, int32> &stopFunction, String &str) noexcept;
		
		FFileStream &ReadToBack(const TFFunction<Bool, int32> &stopFunction) noexcept;
		
		FFileStream &ReadToBack(const TFFunction<Bool, int32> &stopFunction, String &str) noexcept;
		
		FFileStream &ReadToNewLine() noexcept;
		
		FFileStream &ReadLine(String &str) noexcept;
		
		///
		/// 清空错误
		FFileStream &ClearError() noexcept;
		
		///
		/// 清空错误
		const FFileStream &ClearError() const noexcept;
		
	public:
		
		[[nodiscard]] Bool Good() const noexcept override { return !(IsError() || IsEOF()); }
		
		[[nodiscard]] Bool Bad() const noexcept override { return IsError() || IsEOF(); }
		
		int32 Peek() noexcept override { return GetPeek(); }
		
		int32 Read() noexcept override;
		
		FFileStream &Write(ElemT elem) noexcept override;
		
		FFileStream &Flush() noexcept override;
	
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
		
		///
		/// \return 如果换行需要刷新，则为true。
		[[nodiscard]] const Bool &GetIsFlushNewline() const{return m_isFlushNewline;}
		
		/// \param isFlushNewline 如果换行需要刷新，则为true。
		void SetIsFlushNewline(const Bool &isFlushNewline){m_isFlushNewline = isFlushNewline;}
	
	private:
		
		FILE *m_file{};
		int32 m_now{};
		int32 m_peek{};
		Bool m_isCloseF{};
		Bool m_isFlushNewline{};
		
	};
	
	using FileStreamA = FFileStream<CharA>;
	using FileStreamW = FFileStream<CharW>;
	using FileStreamT = FFileStream<CharT>;
	
	
} // Whale

#include "IO.inl"
