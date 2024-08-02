//
// Created by admin on 2024/7/1.
//

#pragma once

#include "TypeDef.hpp"
#include "SourceLocation.hpp"
#include "IO.hpp"

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
	
	template<class ElemT>
	WHALE_API const ElemT *ToString(EDebugLevel lvl);
	
	/// 日志
	class WHALE_API FLogger : public IGoodAndBad
	{
	public:
		
		FLogger();
		
		~FLogger() override;
	
	public:
		
		[[nodiscard]] Bool Good() const noexcept override;
		
		[[nodiscard]] Bool Bad() const noexcept override;
	
	public:
		
		[[nodiscard]] Bool IsError() const noexcept;
		
		[[nodiscard]] Bool IsEOF() const noexcept;
		
		[[nodiscard]] Bool IsOpen() const noexcept;
		
		void Open(const StringA &logDir, const StringA &logFileName);
		
		void Open(const StringW &logDir, const StringW &logFileName);
		
		void Flush();
		
		void Close();
		
		template<class ElemT = Char>
		void Log(EDebugLevel level, const Container::TFString<ElemT> &tag, const Container::TFString<ElemT> &message,
		         const FSourceLocation &sourceLocation = FSourceLocation::Current());
	
	private:
		
		IO::FileStreamA m_fileStreamA;
		
		IO::FileStreamW m_fileStreamW;
		
	};
	
	/// 调试类
	class WHALE_API FDebug
	{
	public:
		
		static void LogToFile(const StringA &logDir, const StringA &logFileName);
		
		static void LogToFile(const StringW &logDir, const StringW &logFileName);
		
		template<class ElemT = Char>
		static void Log(
			EDebugLevel level, const Container::TFString<ElemT> &tag, const Container::TFString<ElemT> &message,
			const FSourceLocation &sourceLocation = FSourceLocation::Current());

//		static void LogToFile(const StringA &logFileName, SizeT rotationSize = 10 * 1024 * 1024);
//
//		static void LogToFile(const StringW &logFileName, SizeT rotationSize = 10 * 1024 * 1024);
//
//		static void Log(const StringA &tag, const StringA &message, EDebugLevel level,
//		                const FSourceLocation &sourceLocation = FSourceLocation::Current());
//
//		static void Log(const StringW &tag, const StringW &message, EDebugLevel level,
//		                const FSourceLocation &sourceLocation = FSourceLocation::Current());
//
//		static void Log(const StringA &tag, const FException &exception, EDebugLevel level,
//		                const FSourceLocation &sourceLocation = FSourceLocation::Current());
//
//		static void Log(const StringW &tag, const FException &exception, EDebugLevel level,
//		                const FSourceLocation &sourceLocation = FSourceLocation::Current());
//
//		static void Log(const CharA *tag, const CharA *message, EDebugLevel level,
//		                const FSourceLocation &sourceLocation = FSourceLocation::Current());
//
//		static void Log(const CharW *tag, const CharW *message, EDebugLevel level,
//		                const FSourceLocation &sourceLocation = FSourceLocation::Current());
		
		///
		/// 刷新日志（将缓冲区的数据写入文件）
		static void LogFlush();
		
		///
		/// 关闭日志
		static void LogClose();
	
	public:
		
		static FLogger m_logger;
		
	};
	
	
} // Whale
