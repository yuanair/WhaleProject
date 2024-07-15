//
// Created by admin on 2024/7/1.
//

#include "FDebug.hpp"

#include <windows.h>

BOOST_LOG_ATTRIBUTE_KEYWORD(tag_attr, "Tag", std::string)
BOOST_LOG_ATTRIBUTE_KEYWORD(scope, "Scope", boost::log::attributes::named_scope::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(timeline, "Timeline", boost::log::attributes::timer::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(thread_id, "ThreadID", boost::log::attributes::current_thread_id::value_type)

namespace Whale
{
	
	void FDebug::LogToFile(const std::string &logFileName, const size_t &rotationSize)
	{
		boost::shared_ptr<FDebug::Backend> backend = boost::make_shared<FDebug::Backend>(
			boost::log::keywords::file_name = logFileName,
			boost::log::keywords::rotation_size = rotationSize,
			boost::log::keywords::open_mode = std::ios_base::app
		);
		
		boost::shared_ptr<FDebug::Sink> sink(new FDebug::Sink(backend));
		
		sink->set_formatter(
			boost::log::expressions::stream
				<< "["
				<< boost::log::trivial::severity << "]["
				<< boost::log::expressions::format_date_time<boost::posix_time::ptime>(
					"TimeStamp", "%Y-%m-%d %H:%M:%S.%f"
				) << "]["
				<< thread_id << "]"
				<< scope
				<< boost::log::expressions::if_(boost::log::expressions::has_attr(tag_attr))
				[
					boost::log::expressions::stream << "[" << tag_attr << "]"
				]
				<< boost::log::expressions::if_(boost::log::expressions::has_attr(timeline))
				[
					boost::log::expressions::stream << "[" << timeline << "]"
				]
				<< ": "
				<< boost::log::expressions::message
		);
		
		boost::log::core::get()->add_sink(sink);
		
		boost::log::add_common_attributes();
		boost::log::core::get()->add_global_attribute("Scope", boost::log::attributes::named_scope());
	}
	
	void FDebug::LogToFile(const std::wstring &logFileName, const size_t &rotationSize)
	{
		boost::shared_ptr<FDebug::Backend> backend = boost::make_shared<FDebug::Backend>(
			boost::log::keywords::file_name = logFileName,
			boost::log::keywords::rotation_size = rotationSize,
			boost::log::keywords::open_mode = std::ios_base::app
		);
		boost::shared_ptr<FDebug::Sink> sink = boost::make_shared<FDebug::Sink>(backend);
		
		sink->set_formatter(
			boost::log::expressions::stream
				<< "["
				<< boost::log::trivial::severity << "]["
				<< boost::log::expressions::format_date_time<boost::posix_time::ptime>(
					"TimeStamp", "%Y-%m-%d %H:%M:%S.%f"
				) << "]["
				<< thread_id << "]"
				<< scope
				<< boost::log::expressions::if_(boost::log::expressions::has_attr(tag_attr))
				[
					boost::log::expressions::stream << "[" << tag_attr << "]"
				]
				<< boost::log::expressions::if_(boost::log::expressions::has_attr(timeline))
				[
					boost::log::expressions::stream << "[" << timeline << "]"
				]
				<< ": "
				<< boost::log::expressions::message
		);
		
		boost::log::core::get()->add_sink(sink);
		
		boost::log::add_common_attributes();
		boost::log::core::get()->add_global_attribute("Scope", boost::log::attributes::named_scope());
	}
	
	void FDebug::Log(const Char *message, boost::log::trivial::severity_level level,
					 const FSourceLocation &sourceLocation)
	{
		BOOST_LOG_SEV(logger, level) << "[" << sourceLocation.FileName() << "(" << sourceLocation.Line()
									 << ", " << sourceLocation.Column() << ")]["
									 << sourceLocation.FunctionName() << "]: " << message;
		if (level >= boost::log::trivial::severity_level::warning) LogFlush();
	}
	
	void FDebug::Log(const WChar *message, boost::log::trivial::severity_level level,
					 const FSourceLocation &sourceLocation)
	{
		BOOST_LOG_SEV(wlogger, level) << "[" << sourceLocation.FileName() << "(" << sourceLocation.Line()
									  << ", " << sourceLocation.Column() << ")]["
									  << sourceLocation.FunctionName() << "]: " << message;
		if (level >= boost::log::trivial::severity_level::warning) LogFlush();
	}
	
	void FDebug::LogFlush()
	{
		boost::log::core::get()->flush();
	}
	
	FDebug::Logger FDebug::logger{};
	
	FDebug::WLogger FDebug::wlogger{};
	
} // Whale