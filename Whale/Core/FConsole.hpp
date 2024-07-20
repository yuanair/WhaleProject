//
// Created by admin on 2024/7/19.
//

#pragma once

#include "TypeDef.hpp"
#include "Whale/Core/IO.hpp"

namespace Whale
{
	
	///
	/// 控制台
	class WHALE_API FConsole
	{
	public:
		
		///
		/// 写入字符串
		/// \param str
		static void Write(const StringA &str);
		
		///
		/// 写入字符串
		/// \param str
		static void Write(const StringW &str);
		
		///
		/// 写入字符串，并换行
		/// \param str
		static void WriteLine(const StringA &str);
		
		///
		/// 写入字符串，并换行
		/// \param str
		static void WriteLine(const StringW &str);
		
		///
		/// \return 读取
		static CharA ReadA();
		
		///
		/// \return 读取
		static CharW ReadW();
		
		///
		/// \return 读取
		static void ReadLine(StringA &str);
		
		///
		/// \return 读取
		static void ReadLine(StringW &str);
	
	public:
		
		static IO::FileStreamA outA;
		
		static IO::FileStreamW outW;
		
		static IO::FileStreamA inA;
		
		static IO::FileStreamW inW;
		
		static IO::FileStreamA errA;
		
		static IO::FileStreamW errW;
		
	};
	
} // Whale
