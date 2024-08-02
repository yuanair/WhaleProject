//
// Created by admin on 2024/7/1.
//

#include "FDebug.hpp"

//#include "boost/log/expressions.hpp"
//#include "boost/log/utility/setup.hpp"
//#include "boost/log/support/date_time.hpp"
//#include "boost/log/attributes.hpp"
//#include "boost/log/attributes/scoped_attribute.hpp"
//#include "boost/log/trivial.hpp"
//
//BOOST_LOG_ATTRIBUTE_KEYWORD(thread_id, "ThreadID", boost::log::attributes::current_thread_id::value_type)

namespace Whale
{
	
	FLogger FDebug::m_logger{};
	
	template<>
	WHALE_API const CharA *ToString(EDebugLevel lvl)
	{
		switch (lvl)
		{
			case Trace:
				return "Trace";
			case Debug:
				return "Debug";
			case Info:
				return "Info";
			case Warning:
				return "Warning";
			case Error:
				return "Error";
			case Fatal:
				return "Fatal";
			default:
				return "<unknown-level>";
		}
	}
	
	template<>
	WHALE_API const CharW *ToString(EDebugLevel lvl)
	{
		switch (lvl)
		{
			case Trace:
				return L"Trace";
			case Debug:
				return L"Debug";
			case Info:
				return L"Info";
			case Warning:
				return L"Warning";
			case Error:
				return L"Error";
			case Fatal:
				return L"Fatal";
			default:
				return L"<unknown-level>";
		}
	}
	
	template<>
	WHALE_API void FLogger::Log<CharA>(EDebugLevel level, const StringA &tag, const StringA &message,
	                                   const FSourceLocation &sourceLocation)
	{
		m_fileStreamA.Write("[");
		m_fileStreamA.Write(ToString<CharA>(level));
		m_fileStreamA.Write("][");
		m_fileStreamA.Write("%Time%");
		m_fileStreamA.Write("][");
		m_fileStreamA.Write("%ThreadId%");
		m_fileStreamA.Write("][");
		m_fileStreamA.Write(sourceLocation.FileName());
		m_fileStreamA.Write("(");
		m_fileStreamA.Write(sourceLocation.Line());
		m_fileStreamA.Write(", ");
		m_fileStreamA.Write(sourceLocation.Column());
		m_fileStreamA.Write(")][");
		m_fileStreamA.Write(sourceLocation.FunctionName());
		m_fileStreamA.Write("]");
		m_fileStreamA.Write(tag);
		m_fileStreamA.Write(": ");
		m_fileStreamA.WriteLine(message);
	}
	
	template<>
	WHALE_API void FLogger::Log<CharW>(EDebugLevel level, const StringW &tag, const StringW &message,
	                                   const FSourceLocation &sourceLocation)
	{
		m_fileStreamW.Write(L"[");
		m_fileStreamW.Write(ToString<CharW>(level));
		m_fileStreamW.Write(L"][");
		m_fileStreamW.Write(L"%Time%");
		m_fileStreamW.Write(L"][");
		m_fileStreamW.Write(L"%ThreadId%");
		m_fileStreamW.Write(L"][");
		m_fileStreamW.Write(FLocale::ToUTFString(sourceLocation.FileName(), "UTF-8"));
		m_fileStreamW.Write(L"(");
		m_fileStreamW.Write(sourceLocation.Line());
		m_fileStreamW.Write(L", ");
		m_fileStreamW.Write(sourceLocation.Column());
		m_fileStreamW.Write(L")][");
		m_fileStreamW.Write(FLocale::ToUTFString(sourceLocation.FunctionName(), "UTF-8"));
		m_fileStreamW.Write(L"]");
		m_fileStreamW.Write(tag);
		m_fileStreamW.Write(L": ");
		m_fileStreamW.WriteLine(message);
	}

//	typedef boost::log::sinks::text_file_backend Backend;
//
//	typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend> Sink;
//
//	typedef boost::log::sources::severity_logger_mt<EDebugLevel> LoggerA;
//
//	typedef boost::log::sources::wseverity_logger_mt<EDebugLevel> LoggerW;
//
//	static boost::shared_ptr<LoggerA> logger;
//
//	static boost::shared_ptr<LoggerW> wLogger;
//
//	static boost::shared_ptr<Sink> sink;

//	template<class T>
//	inline void LogToFile(const T &logFileName, SizeT rotationSize)
//	{
//
//		boost::shared_ptr<Backend> backend = boost::make_shared<Backend>(
//			boost::log::keywords::file_name = logFileName.CStr(),
//			boost::log::keywords::rotation_size = rotationSize,
//			boost::log::keywords::open_mode = std::ios_base::app
//		);
//
//		sink = boost::make_shared<Sink>(backend);
//
//		sink->set_formatter(
//			boost::log::expressions::stream
//				<< "[" << boost::log::expressions::attr<EDebugLevel>("Severity")
//				<< "][" << boost::log::expressions::format_date_time<boost::posix_time::ptime>
//					(
//						"TimeStamp", "%Y-%m-%d %H:%M:%S.%f"
//					)
//				<< "][" << thread_id << "]" << boost::log::expressions::message
//		);
//
//		boost::log::core::get()->add_sink(sink);
//
//		boost::log::add_common_attributes();
//
//		logger  = boost::make_shared<LoggerA>();
//		wLogger = boost::make_shared<LoggerW>();
//
//	}
//
//	template<class T, class U>
//	void LogA(T tag, U message, EDebugLevel level, const FSourceLocation &sourceLocation)
//	{
//		BOOST_LOG_SEV(*logger, level) << "[" << sourceLocation.FileName() << "(" << sourceLocation.Line() << ", "
//		                              << sourceLocation.Column() << ")][" << sourceLocation.FunctionName() << "]" << tag
//		                              << ": " << message;
//		if (level >= EDebugLevel::Warning)
//		{
//			FDebug::LogFlush();
//		}
//	}
//
//	template<class T, class U>
//	void LogW(T tag, U message, EDebugLevel level, const FSourceLocation &sourceLocation)
//	{
//		BOOST_LOG_SEV(*wLogger, level) << L"[" << sourceLocation.FileName() << L"(" << sourceLocation.Line() << L", "
//		                               << sourceLocation.Column() << L")][" << sourceLocation.FunctionName() << L"]"
//		                               << tag
//		                               << L": " << message;
//		if (level >= EDebugLevel::Warning)
//		{
//			FDebug::LogFlush();
//		}
//	}
//

//	void FDebug::LogToFile(const StringA &logFileName, SizeT rotationSize)
//	{
//		Whale::LogToFile(logFileName, rotationSize);
//	}
//
//	void FDebug::LogToFile(const StringW &logFileName, SizeT rotationSize)
//	{
//		Whale::LogToFile(logFileName, rotationSize);
//	}
//
//	void FDebug::Log(const StringA &tag, const StringA &message, EDebugLevel level,
//	                 const FSourceLocation &sourceLocation)
//	{
//		Whale::LogA(tag.CStr(), message.CStr(), level, sourceLocation);
//	}
//
//	void FDebug::Log(const StringW &tag, const StringW &message, EDebugLevel level,
//	                 const FSourceLocation &sourceLocation)
//	{
//		Whale::LogW(tag.CStr(), message.CStr(), level, sourceLocation);
//	}
//
//	void FDebug::Log(const StringA &tag, const FException &exception, EDebugLevel level,
//	                 const FSourceLocation &sourceLocation)
//	{
//		Whale::LogA(tag.CStr(), exception.What(), level, sourceLocation);
//	}
//
//	void FDebug::Log(const StringW &tag, const FException &exception, EDebugLevel level,
//	                 const FSourceLocation &sourceLocation)
//	{
//		Whale::LogW(tag.CStr(), exception.What(), level, sourceLocation);
//	}
//
//	void FDebug::Log(const CharA *tag, const CharA *message, EDebugLevel level, const FSourceLocation &sourceLocation)
//	{
//		Whale::LogA(tag, message, level, sourceLocation);
//	}
//
//	void FDebug::Log(const CharW *tag, const CharW *message, EDebugLevel level, const FSourceLocation &sourceLocation)
//	{
//		Whale::LogW(tag, message, level, sourceLocation);
//	}

//	void FDebug::LogFlush()
//	{
//		boost::log::core::get()->flush();
//	}
//
//	void FDebug::LogClose()
//	{
//		LogFlush();
//		boost::log::core::get()->remove_sink(sink);
//		sink.reset();
//		logger.reset();
//		wLogger.reset();
//	}
//
	
	void FDebug::LogFlush()
	{
		m_logger.Flush();
	}
	
	void FDebug::LogClose()
	{
		LogFlush();
		m_logger.Close();
	}
	
	void FDebug::LogToFile(const StringA &logDir, const StringA &logFileName)
	{
		m_logger.Open(logDir, logFileName);
	}
	
	void FDebug::LogToFile(const StringW &logDir, const StringW &logFileName)
	{
		m_logger.Open(logDir, logFileName);
	}
	
	template<>
	WHALE_API void FDebug::Log<CharA>(EDebugLevel level, const StringA &tag, const StringA &message,
	                                  const FSourceLocation &sourceLocation)
	{
		m_logger.Log<CharA>(level, tag, message, sourceLocation);
		if (level >= Warning)
		{
			LogFlush();
		}
	}
	
	template<>
	WHALE_API void FDebug::Log<CharW>(EDebugLevel level, const StringW &tag, const StringW &message,
	                                  const FSourceLocation &sourceLocation)
	{
		m_logger.Log<CharW>(level, tag, message, sourceLocation);
		if (level >= Warning)
		{
			LogFlush();
		}
	}
	
	FLogger::FLogger()
	{
	
	}
	
	
	FLogger::~FLogger()
	{
	
	}
	
	Bool FLogger::Good() const noexcept
	{
		return m_fileStreamA.Good() && m_fileStreamW.Good();
	}
	
	Bool FLogger::Bad() const noexcept
	{
		return m_fileStreamA.Bad() || m_fileStreamW.Bad();
	}
	
	Bool FLogger::IsError() const noexcept
	{
		return m_fileStreamA.IsError() || m_fileStreamW.IsError();
	}
	
	Bool FLogger::IsEOF() const noexcept
	{
		return m_fileStreamA.IsEOF() || m_fileStreamW.IsEOF();
	}
	
	Bool FLogger::IsOpen() const noexcept
	{
		return m_fileStreamA.IsOpen() && m_fileStreamW.IsOpen();
	}
	
	void FLogger::Open(const StringA &logDir, const StringA &logFileName)
	{
		m_fileStreamA.Open(logDir + logFileName, "w+");
		m_fileStreamW.Open(logDir + logFileName, "w+");
	}
	
	void FLogger::Open(const StringW &logDir, const StringW &logFileName)
	{
		
		m_fileStreamA.Open(logDir + logFileName, L"w+");
		m_fileStreamW.Open(logDir + logFileName, L"w+");
	}
	
	void FLogger::Flush()
	{
		m_fileStreamA.Flush();
		m_fileStreamW.Flush();
	}
	
	void FLogger::Close()
	{
		m_fileStreamA.Close();
		m_fileStreamW.Close();
	}
	
	
} // Whale