//
// Created by admin on 2024/7/1.
//

#pragma once

#include "Whale/Core/Tool/FTypeDef.hpp"
#include "Whale/Render/Win32/FMessageBox.hpp"
#include "Whale/Render/Win32/FCore.hpp"
#include "Whale/Core/Tool/FSourceLocation.hpp"

namespace Whale
{
	
	///
	/// 级别
	enum EDebugLevel
	{
		Trace,
		Debug,
		Info,
		Warning,
		Error,
		Fatal
	};
	
	WHALE_API const Char *ToString(EDebugLevel lvl);
	
	/// 调试类
	class WHALE_API FDebug
	{
	public:
		
		static void LogToFile(const FTStringA &logFileName, SizeT rotationSize = 10 * 1024 * 1024);
		
		static void LogToFile(const FTStringW &logFileName, SizeT rotationSize = 10 * 1024 * 1024);
		
		static void Log(const FTStringA &tag, const FTStringA &message, EDebugLevel level,
						const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
		static void Log(const FTStringW &tag, const FTStringW &message, EDebugLevel level,
						const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
		static void Log(const Char *tag, const Char *message, EDebugLevel level,
						const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
		static void Log(const WChar *tag, const WChar *message, EDebugLevel level,
						const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
		
		template<typename T1, typename T2>
		inline static void
		LogTrace(T1 tag, T2 message, const FSourceLocation &sourceLocation = FSourceLocation::Current())
		{
			Log(tag, message, EDebugLevel::Trace, sourceLocation);
		}
		
		template<typename T1, typename T2>
		inline static void
		LogDebug(T1 tag, T2 message, const FSourceLocation &sourceLocation = FSourceLocation::Current())
		{
			Log(tag, message, EDebugLevel::Debug, sourceLocation);
		}
		
		template<typename T1, typename T2>
		inline static void
		LogInfo(T1 tag, T2 message, const FSourceLocation &sourceLocation = FSourceLocation::Current())
		{
			Log(tag, message, EDebugLevel::Info, sourceLocation);
		}
		
		template<typename T1, typename T2>
		inline static void
		LogWarning(T1 tag, T2 message, const FSourceLocation &sourceLocation = FSourceLocation::Current())
		{
			Log(tag, message, EDebugLevel::Warning, sourceLocation);
		}
		
		template<typename T1, typename T2>
		inline static void
		LogError(T1 tag, T2 message, const FSourceLocation &sourceLocation = FSourceLocation::Current())
		{
			Log(tag, message, EDebugLevel::Error, sourceLocation);
		}
		
		template<typename T1, typename T2>
		inline static void
		LogFatal(T1 tag, T2 message, const FSourceLocation &sourceLocation = FSourceLocation::Current())
		{
			Log(tag, message, EDebugLevel::Fatal, sourceLocation);
		}
		
		template<typename T1, typename T2>
		inline static void
		Fatal(T1 tag, T2 message, const FSourceLocation &sourceLocation = FSourceLocation::Current())
		{
			LogFatal(tag, message, sourceLocation);
			Win32::FMessageBox::Show(message, tag, Win32::FMessageBoxIconStop);
			Win32::FCore::Exit(0);
		}
		
		///
		/// 刷新日志（将缓冲区的数据写入文件）
		static void LogFlush();
		
	};
	
	
} // Whale
