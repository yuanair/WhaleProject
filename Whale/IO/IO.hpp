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
	errno_t FileOpen(FILE **pFile, const ElemT *fileName, const ElemT *openMode) noexcept;
	
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
	/// 文件
	template<class ElemT>
	class WHALE_API FFileStream : public TIStream<ElemT>
	{
	public:
		
		using String = TIStream<ElemT>::String;
	
	public:
		
		FFileStream() noexcept: myChar(0), isWroteSome(false), isCloseF(false), myFile(nullptr) {}
		
		FFileStream(FILE *file, Bool isCloseF) noexcept: myChar(0), isWroteSome(false), isCloseF(isCloseF),
		                                                 myFile(file) {}
		
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
		
		ElemT Peek();
		
		Bool Get(ElemT &elem) override;
		
		Bool UnGet(ElemT &elem) override;
		
		Bool Put(ElemT elem) override;
		
		template<class... Args>
		Bool Puts(ElemT elem, Args... args);
		
		Bool Flush() override;
		
		Bool ReadToNewLine();
		
		Bool Write(const String &str);
		
		Bool WriteLine(const String &str);
		
		Bool Read(String &str) override;
		
		Bool ReadTo(const std::function<Bool(ElemT)> &stopFunction);
		
		Bool ReadTo(String &str, const std::function<Bool(ElemT)> &stopFunction);
		
		Bool ReadLine(String &str);
	
	
	public:
		
		///
		/// \return 如果需要自导序列，则为true。
		[[nodiscard]] bool IsWroteSome() const noexcept { return this->isWroteSome; }
		
		///
		/// \return 如果C流必须关闭，则为true。
		[[nodiscard]] bool IsCloseF() const noexcept { return this->isCloseF; }
		
		///
		/// \return 指向C流的指针
		[[nodiscard]] FILE *GetMyFile() const noexcept { return this->myFile; }
	
	private:
		
		// const _Cvt* pcvt;//指向编解码面的指针(可能为空)。
		ElemT myChar;
		bool isWroteSome;
		bool isCloseF;
		FILE *myFile;
		
	};
	
	using FileStreamA = FFileStream<CharA>;
	using FileStreamW = FFileStream<CharW>;
	using FileStreamT = FFileStream<CharT>;
	
	
} // Whale

#include "IO.inl"
