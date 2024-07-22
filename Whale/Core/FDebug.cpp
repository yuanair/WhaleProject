//
// Created by admin on 2024/7/1.
//

#include "FDebug.hpp"

#include "boost/log/expressions.hpp"
#include "boost/log/utility/setup.hpp"
#include "boost/log/support/date_time.hpp"
#include "boost/log/attributes.hpp"
#include "boost/log/attributes/scoped_attribute.hpp"
#include "boost/log/trivial.hpp"

BOOST_LOG_ATTRIBUTE_KEYWORD(thread_id, "ThreadID", boost::log::attributes::current_thread_id::value_type)

namespace Whale
{
	
	typedef boost::log::sinks::text_file_backend Backend;
	
	typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend> Sink;
	
	typedef boost::log::sources::severity_logger_mt<EDebugLevel> Logger;
	
	typedef boost::log::sources::wseverity_logger_mt<EDebugLevel> WLogger;
	
	static boost::shared_ptr<Logger> logger;
	
	static boost::shared_ptr<WLogger> wLogger;
	
	static boost::shared_ptr<Sink> sink;
	
	template<class T>
	inline void LogToFile(const T &logFileName, SizeT rotationSize)
	{
		
		boost::shared_ptr<Backend> backend = boost::make_shared<Backend>(
			boost::log::keywords::file_name = logFileName.CStr(),
			boost::log::keywords::rotation_size = rotationSize,
			boost::log::keywords::open_mode = std::ios_base::app
		);
		
		sink = boost::make_shared<Sink>(backend);
		
		sink->set_formatter(
			boost::log::expressions::stream
				<< "[" << boost::log::expressions::attr<EDebugLevel>("Severity")
				<< "][" << boost::log::expressions::format_date_time<boost::posix_time::ptime>
					(
						"TimeStamp", "%Y-%m-%d %H:%M:%S.%f"
					)
				<< "][" << thread_id << "]" << boost::log::expressions::message
		);
		
		boost::log::core::get()->add_sink(sink);
		
		boost::log::add_common_attributes();
		
		logger = boost::make_shared<Logger>();
		wLogger = boost::make_shared<WLogger>();
		
	}
	
	template<class T, class U>
	void LogA(T tag, U message, EDebugLevel level, const FSourceLocation &sourceLocation)
	{
		BOOST_LOG_SEV(*logger, level) << "[" << sourceLocation.FileName() << "(" << sourceLocation.Line() << ", "
		                              << sourceLocation.Column() << ")][" << sourceLocation.FunctionName() << "]" << tag
		                              << ": " << message;
		if (level >= EDebugLevel::Warning) FDebug::LogFlush();
	}
	
	template<class T, class U>
	void LogW(T tag, U message, EDebugLevel level, const FSourceLocation &sourceLocation)
	{
		BOOST_LOG_SEV(*wLogger, level) << L"[" << sourceLocation.FileName() << L"(" << sourceLocation.Line() << L", "
		                               << sourceLocation.Column() << L")][" << sourceLocation.FunctionName() << L"]"
		                               << tag
		                               << L": " << message;
		if (level >= EDebugLevel::Warning) FDebug::LogFlush();
	}
	
	
	void FDebug::LogToFile(const StringA &logFileName, SizeT rotationSize)
	{
		Whale::LogToFile(logFileName, rotationSize);
	}
	
	void FDebug::LogToFile(const StringW &logFileName, SizeT rotationSize)
	{
		Whale::LogToFile(logFileName, rotationSize);
	}
	
	void FDebug::Log(const StringA &tag, const StringA &message, EDebugLevel level,
	                 const FSourceLocation &sourceLocation)
	{
		Whale::LogA(tag.CStr(), message.CStr(), level, sourceLocation);
	}
	
	void FDebug::Log(const StringW &tag, const StringW &message, EDebugLevel level,
	                 const FSourceLocation &sourceLocation)
	{
		Whale::LogW(tag.CStr(), message.CStr(), level, sourceLocation);
	}
	
	void FDebug::Log(const StringA &tag, const FException &exception, EDebugLevel level,
	                 const FSourceLocation &sourceLocation)
	{
		Whale::LogA(tag.CStr(), exception.What(), level, sourceLocation);
	}
	
	void FDebug::Log(const StringW &tag, const FException &exception, EDebugLevel level,
	                 const FSourceLocation &sourceLocation)
	{
		Whale::LogW(tag.CStr(), exception.What(), level, sourceLocation);
	}
	
	void FDebug::Log(const CharA *tag, const CharA *message, EDebugLevel level, const FSourceLocation &sourceLocation)
	{
		Whale::LogA(tag, message, level, sourceLocation);
	}
	
	void FDebug::Log(const CharW *tag, const CharW *message, EDebugLevel level, const FSourceLocation &sourceLocation)
	{
		Whale::LogW(tag, message, level, sourceLocation);
	}
	
	void FDebug::LogFlush()
	{
		boost::log::core::get()->flush();
	}
	
	void FDebug::LogClose()
	{
		LogFlush();
		boost::log::core::get()->remove_sink(sink);
		sink.reset();
		logger.reset();
		wLogger.reset();
	}
	
	const CharA *ToString(EDebugLevel lvl)
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
	
	std::ostream &operator<<(std::ostream &strm, EDebugLevel level)
	{
		return strm << ToString(level);
	}
	
} // Whale