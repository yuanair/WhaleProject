//
// Created by admin on 2024/7/19.
//

#pragma once

#include "TypeDef.hpp"
#include "Whale/IO/IO.hpp"

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
		/// 写入字符串
		/// \param str
		static void Write(const String &str);
		
		///
		/// 写入字符串，并换行
		/// \param str
		static void WriteLine(const String &str);
		
		///
		/// \return 读取到空白
		static void Read(String &str);
		
		///
		/// \return 读取一行
		static void ReadLine(String &str);
		
		///
		/// 清空控制台
		static void Clear();
		
		///
		/// 清空输入缓冲区
		static void ClearInBuffer();
		
		///
		/// \return 是否为新行
		static Bool IsNewLine(const String &);
	
	public:
		
		static FileStream out;
		
		static FileStream in;
		
		static FileStream err;
		
	};
	
	using ConsoleA = TFConsole<CharA>;
	using ConsoleW = TFConsole<CharW>;
	using ConsoleT = TFConsole<CharT>;
	
	template<class ElemT>
	void TFConsole<ElemT>::Write(const String &str)
	{
		out.Write(str);
	}
	
	template<class ElemT>
	void TFConsole<ElemT>::WriteLine(const String &str)
	{
		out.WriteLine(str);
	}
	
	template<class ElemT>
	void TFConsole<ElemT>::Read(String &str)
	{
		in.Read(str);
	}
	
	template<class ElemT>
	void TFConsole<ElemT>::ReadLine(String &str)
	{
		in.ReadLine(str);
	}
	
	template<class ElemT>
	void TFConsole<ElemT>::Clear()
	{
		system("cls");
	}
	
	template<class ElemT>
	void TFConsole<ElemT>::ClearInBuffer()
	{
		in.ReadToNewLine();
	}
	
	template<class ElemT>
	Bool TFConsole<ElemT>::IsNewLine(const String &)
	{
		return FLocale::IsNewLine(in.Peek());
	}
	
	template<class ElemT>
	TFConsole<ElemT>::FileStream TFConsole<ElemT>::out{stdout, false};
	
	template<class ElemT>
	TFConsole<ElemT>::FileStream TFConsole<ElemT>::in{stdin, false};
	
	template<class ElemT>
	TFConsole<ElemT>::FileStream TFConsole<ElemT>::err{stderr, false};
	
} // Whale
