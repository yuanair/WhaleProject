//
// Created by admin on 2024/7/1.
//

#pragma once

#include "TypeDef.hpp"
#include "SourceLocation.hpp"

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
	
	WHALE_API const CharA *ToString(EDebugLevel lvl);
	
	/// 调试类
	class WHALE_API FDebug
	{
	public:
		
		static void LogToFile(const StringA &logFileName, SizeT rotationSize = 10 * 1024 * 1024);
		
		static void LogToFile(const StringW &logFileName, SizeT rotationSize = 10 * 1024 * 1024);
		
		static void Log(const StringA &tag, const StringA &message, EDebugLevel level,
		                const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
		static void Log(const StringW &tag, const StringW &message, EDebugLevel level,
		                const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
		static void Log(const CharA *tag, const CharA *message, EDebugLevel level,
		                const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
		static void Log(const CharW *tag, const CharW *message, EDebugLevel level,
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
		
		///
		/// 刷新日志（将缓冲区的数据写入文件）
		static void LogFlush();
		
		///
		/// 关闭日志
		static void LogClose();
		
	};
	
	
} // Whale
