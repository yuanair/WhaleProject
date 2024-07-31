//
// Created by admin on 2024/7/19.
//

#pragma once

#include "TypeDef.hpp"
#include "IO.hpp"

namespace Whale
{
	
	///
	/// 控制台
	template<class ElemT>
	class WHALE_API TFConsole
	{
	public:
		
		using String = Container::TFString<ElemT>;
		
		using FileStream = IO::FFileStream<ElemT>;
	
	public:
		
		///
		/// 清空控制台
		static void Clear() noexcept;
	
	public:
		
		///
		/// 写入字符串
		/// \param str
		void Write(const String &str) noexcept;
		
		///
		/// 写入字符串，并换行
		/// \param str
		void WriteLine(const String &str) noexcept;
		
		///
		/// \return 读取到空白
		void Read(String &str) noexcept;
		
		///
		/// \return 读取一行
		void ReadLine(String &str) noexcept;
		
		///
		/// 清空输入缓冲区
		void ClearInBuffer() noexcept;
		
		///
		/// 清空错误
		void ClearError() const noexcept;
		
		///
		/// \return 是否为新行
		Bool IsNewLine(const String &) noexcept;
	
	public:
		
		FileStream out{stdout, false, true};
		
		FileStream in{stdin, false, true};
		
		FileStream err{stderr, false, true};
		
	};
	
	using ConsoleA = TFConsole<CharA>;
	using ConsoleW = TFConsole<CharW>;
	using ConsoleT = TFConsole<CharT>;
	
	template<class ElemT>
	void TFConsole<ElemT>::Write(const String &str) noexcept
	{
		out.Write(str);
	}
	
	template<class ElemT>
	void TFConsole<ElemT>::WriteLine(const String &str) noexcept
	{
		out.WriteLine(str);
	}
	
	template<class ElemT>
	void TFConsole<ElemT>::Read(String &str) noexcept
	{
		in.Read(str);
	}
	
	template<class ElemT>
	void TFConsole<ElemT>::ReadLine(String &str) noexcept
	{
		in.ReadLine(str);
	}
	
	template<class ElemT>
	void TFConsole<ElemT>::Clear() noexcept
	{
		system("cls");
	}
	
	template<class ElemT>
	void TFConsole<ElemT>::ClearInBuffer() noexcept
	{
		if (!FLocale::IsNewLine(in.Peek())) in.ReadToNewLine();
	}
	
	template<class ElemT>
	void TFConsole<ElemT>::ClearError() const noexcept
	{
		in.ClearError();
		out.ClearError();
		err.ClearError();
	}
	
	template<class ElemT>
	Bool TFConsole<ElemT>::IsNewLine(const String &) noexcept
	{
		return FLocale::IsNewLine(in.GetPeek());
	}
	
} // Whale
