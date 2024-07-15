//
// Created by admin on 2024/7/1.
//

#pragma once

#include "FTypeDef.hpp"
#include "Whale/Win32/FMessageBox.hpp"
#include "Whale/Win32/FCore.hpp"
#include "FSourceLocation.hpp"

#include <string>

#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/attributes.hpp>

namespace Whale
{
	
	// 调试
	class WHALE_API FDebug
	{
	public:
		
		template<class CharT>
		struct Info
		{
			FSourceLocation sourceLocation;
			const CharT *message;
		};
		
		using InfoA = Info<Char>;
		
		using InfoW = Info<WChar>;
	
	public:
		
		typedef boost::log::sinks::text_file_backend Backend;
		
		typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend> Sink;
		
		typedef boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level> Logger;
		
		typedef boost::log::sources::wseverity_logger_mt<boost::log::trivial::severity_level> WLogger;
	
	public:
		
		static void LogToFile(const std::string &logFileName,
							  const size_t &rotationSize = 10 * 1024 * 1024);
		
		static void LogToFile(const std::wstring &logFileName,
							  const size_t &rotationSize = 10 * 1024 * 1024);
		
		static void Log(const Char *message, boost::log::trivial::severity_level level,
						const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
		static void Log(const WChar *message, boost::log::trivial::severity_level level,
						const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
		
		template<typename T>
		inline static void
		LogTrace(const T *message, const FSourceLocation &sourceLocation = FSourceLocation::Current())
		{
			Log(message, boost::log::trivial::trace, sourceLocation);
		}
		
		template<typename T>
		inline static void
		LogDebug(const T *message, const FSourceLocation &sourceLocation = FSourceLocation::Current())
		{
			Log(message, boost::log::trivial::debug, sourceLocation);
		}
		
		template<typename T>
		inline static void
		LogInfo(const T *message, const FSourceLocation &sourceLocation = FSourceLocation::Current())
		{
			Log(message, boost::log::trivial::info, sourceLocation);
		}
		
		template<typename T>
		inline static void
		LogWarning(const T *message, const FSourceLocation &sourceLocation = FSourceLocation::Current())
		{
			Log(message, boost::log::trivial::warning, sourceLocation);
		}
		
		template<typename T>
		inline static void
		LogError(const T *message, const FSourceLocation &sourceLocation = FSourceLocation::Current())
		{
			Log(message, boost::log::trivial::error, sourceLocation);
		}
		
		template<typename T>
		inline static void
		LogFatal(const T *message, const FSourceLocation &sourceLocation = FSourceLocation::Current())
		{
			Log(message, boost::log::trivial::fatal, sourceLocation);
		}
		
		template<typename T>
		inline static void
		Fatal(const T *message, const FSourceLocation &sourceLocation = FSourceLocation::Current())
		{
			LogFatal(message, sourceLocation);
			Win32::FMessageBox::Show(message, Win32::FMessageBoxIconStop);
			Win32::FCore::Exit(0);
		}
		
		///
		/// 刷新日志（将缓冲区的数据写入文件）
		static void LogFlush();
	
	private:
		
		static Logger logger;
		
		static WLogger wlogger;
		
	};
	
} // Whale
