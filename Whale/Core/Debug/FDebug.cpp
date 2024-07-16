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

//BOOST_LOG_ATTRIBUTE_KEYWORD(tag_attr, "Tag", const Whale::Char*)
//BOOST_LOG_ATTRIBUTE_KEYWORD(file_attr, "File", const Whale::Char*)
//BOOST_LOG_ATTRIBUTE_KEYWORD(line_attr, "Line", Whale::uint32)
//BOOST_LOG_ATTRIBUTE_KEYWORD(column_attr, "Column", Whale::uint32)
//BOOST_LOG_ATTRIBUTE_KEYWORD(function_attr, "Function", const Whale::Char*)
BOOST_LOG_ATTRIBUTE_KEYWORD(thread_id, "ThreadID", boost::log::attributes::current_thread_id::value_type)

namespace Whale
{
	
	typedef boost::log::sinks::text_file_backend Backend;
	
	typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend> Sink;
	
	typedef boost::log::sources::severity_logger_mt<EDebugLevel> Logger;
	
	typedef boost::log::sources::wseverity_logger_mt<EDebugLevel> WLogger;
	
	static Logger logger{};
	
	static WLogger wlogger{};
	
	template<class T>
	inline void LogToFile(const T &logFileName, SizeT rotationSize)
	{
		boost::shared_ptr<Backend> backend = boost::make_shared<Backend>(
			boost::log::keywords::file_name = logFileName.CStr(),
			boost::log::keywords::rotation_size = rotationSize,
			boost::log::keywords::open_mode = std::ios_base::app
		);
		
		boost::shared_ptr<Sink> sink = boost::make_shared<Sink>(backend);
		
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
		// boost::log::core::get()->add_global_attribute("Scope", boost::log::attributes::named_scope());
	}
	
	template<class T>
	void Log(T tag, T message, EDebugLevel level, const FSourceLocation &sourceLocation)
	{
//		BOOST_LOG_SCOPED_THREAD_ATTR("Tag", boost::log::attributes::constant<T>(tag));
//		BOOST_LOG_SCOPED_THREAD_ATTR("File",
//									 boost::log::attributes::constant<const Whale::Char *>(sourceLocation.FileName()));
//		BOOST_LOG_SCOPED_THREAD_ATTR("Line", boost::log::attributes::constant<Whale::uint32>(sourceLocation.Line()));
//		BOOST_LOG_SCOPED_THREAD_ATTR("Column",
//									 boost::log::attributes::constant<Whale::uint32>(sourceLocation.Column()));
//		BOOST_LOG_SCOPED_THREAD_ATTR("Function", boost::log::attributes::constant<const Whale::Char *>(
//			sourceLocation.FunctionName()));
		BOOST_LOG_SEV(logger, level) << "[" << sourceLocation.FileName() << "(" << sourceLocation.Line() << ", "
									 << sourceLocation.Column() << ")][" << sourceLocation.FunctionName() << "]" << tag
									 << ": " << message;
		if (level >= EDebugLevel::Warning) FDebug::LogFlush();
	}
	
	
	void FDebug::LogToFile(const FTStringA &logFileName, SizeT rotationSize)
	{
		Whale::LogToFile(logFileName, rotationSize);
	}
	
	void FDebug::LogToFile(const FTStringW &logFileName, SizeT rotationSize)
	{
		Whale::LogToFile(logFileName, rotationSize);
	}
	
	void FDebug::Log(const FTStringA &tag, const FTStringA &message, EDebugLevel level,
					 const FSourceLocation &sourceLocation)
	{
		Whale::Log<const Char *>(tag.CStr(), message.CStr(), level, sourceLocation);
	}
	
	void FDebug::Log(const FTStringW &tag, const FTStringW &message, EDebugLevel level,
					 const FSourceLocation &sourceLocation)
	{
		Whale::Log<const WChar *>(tag.CStr(), message.CStr(), level, sourceLocation);
	}
	
	void FDebug::Log(const Char *tag, const Char *message, EDebugLevel level, const FSourceLocation &sourceLocation)
	{
		Whale::Log(tag, message, level, sourceLocation);
	}
	
	void FDebug::Log(const WChar *tag, const WChar *message, EDebugLevel level, const FSourceLocation &sourceLocation)
	{
		Whale::Log(tag, message, level, sourceLocation);
	}
	
	void FDebug::LogFlush()
	{
		boost::log::core::get()->flush();
	}
	
	const Char *ToString(EDebugLevel lvl)
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