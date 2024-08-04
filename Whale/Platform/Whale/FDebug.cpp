//
// Created by admin on 2024/7/1.
//

#include "FDebug.hpp"

#include "FPlatformManager.hpp"
#include "WGenericFileManager.hpp"

//#include "boost/log/expressions.hpp"
//#include "boost/log/utility/setup.hpp"
//#include "boost/log/support/date_time.hpp"
//#include "boost/log/attributes.hpp"
//#include "boost/log/attributes/scoped_attribute.hpp"
//#include "boost/log/trivial.hpp"
//
//BOOST_LOG_ATTRIBUTE_KEYWORD(thread_id, "ThreadID", boost::log::attributes::current_thread_id::value_type)

#include <Windows.h>

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
		m_pFile->Write(FPlatformManager::Get().GetLocale().ToAString(++count));
		m_pFile->Write("[");
		m_pFile->Write(ToString<CharA>(level));
		m_pFile->Write("][");
		m_pFile->Write("%Time%");
		m_pFile->Write("][");
		m_pFile->Write("%ThreadId%");
		m_pFile->Write("][");
		m_pFile->Write(sourceLocation.FileName());
		m_pFile->Write("(");
		m_pFile->Write(FPlatformManager::Get().GetLocale().ToAString(sourceLocation.Line()));
		m_pFile->Write(", ");
		m_pFile->Write(FPlatformManager::Get().GetLocale().ToAString(sourceLocation.Column()));
		m_pFile->Write(")][");
		m_pFile->Write(sourceLocation.FunctionName());
		m_pFile->Write("]");
		m_pFile->Write(tag);
		m_pFile->Write(": ");
		m_pFile->WriteLine(message);
		if (level >= Warning)
		{
			::OutputDebugStringA(message.CStr());
			m_pFile->Flush();
		}
	}
	
	template<>
	WHALE_API void FLogger::Log<CharW>(EDebugLevel level, const StringW &tag, const StringW &message,
	                                   const FSourceLocation &sourceLocation)
	{
		m_pFile->Write(FPlatformManager::Get().GetLocale().ToAString(++count));
		m_pFile->Write(L"|[");
		m_pFile->Write(ToString<CharW>(level));
		m_pFile->Write(L"][");
		m_pFile->Write(L"%Time%");
		m_pFile->Write(L"][");
		m_pFile->Write(L"%ThreadId%");
		m_pFile->Write(L"][");
		m_pFile->Write(sourceLocation.FileName());
		m_pFile->Write(L"(");
		m_pFile->Write(FPlatformManager::Get().GetLocale().ToAString(sourceLocation.Line()));
		m_pFile->Write(", ");
		m_pFile->Write(FPlatformManager::Get().GetLocale().ToAString(sourceLocation.Column()));
		m_pFile->Write(L")][");
		m_pFile->Write(sourceLocation.FunctionName());
		m_pFile->Write(L"]");
		m_pFile->Write(tag);
		m_pFile->Write(L": ");
		m_pFile->WriteLine(message);
		if (level >= Warning)
		{
			::OutputDebugStringW(message.CStr());
			m_pFile->Flush();
		}
	}
	
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
	}
	
	template<>
	WHALE_API void FDebug::Log<CharW>(EDebugLevel level, const StringW &tag, const StringW &message,
	                                  const FSourceLocation &sourceLocation)
	{
		m_logger.Log<CharW>(level, tag, message, sourceLocation);
	}
	
	FLogger::FLogger()
		: m_pFile(FPlatformManager::Get().GetFileManager().PreOpenFile()), count(0)
	{
	
	}
	
	
	FLogger::~FLogger() = default;
	
	Bool FLogger::IsOpened() const noexcept
	{
		return m_pFile->IsOpened();
	}
	
	void FLogger::Open(const StringA &logDir, const StringA &logFileName)
	{
		m_pFile->Open(logDir + "/" + logFileName, EFileOpenModeWrite, EFileSharedModeRead, EFileCreateModeNoFound);
		m_pFile->SetPosToEnd();
	}
	
	void FLogger::Open(const StringW &logDir, const StringW &logFileName)
	{
		m_pFile->Open(logDir + L"/" + logFileName, EFileOpenModeWrite, EFileSharedModeRead, EFileCreateModeNoFound);
		m_pFile->SetPosToEnd();
	}
	
	void FLogger::Flush()
	{
		m_pFile->Flush();
	}
	
	void FLogger::Close()
	{
		m_pFile->Close();
	}
	
	
} // Whale