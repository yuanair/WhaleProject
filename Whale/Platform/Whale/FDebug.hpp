//
// Created by admin on 2024/7/1.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/SourceLocation.hpp>
#include "WGenericFile.hpp"

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
	class WHALE_API FLogger
	{
	public:
		
		FLogger();
		
		~FLogger();
	
	public:
		
		[[nodiscard]] Bool IsOpened() const noexcept;
		
		void Open(const StringA &logDir, const StringA &logFileName);
		
		void Open(const StringW &logDir, const StringW &logFileName);
		
		void Flush();
		
		void Close();
		
		template<class ElemT = Char>
		void Log(EDebugLevel level, const Container::TFString<ElemT> &tag, const Container::TFString<ElemT> &message,
		         const FSourceLocation &sourceLocation = FSourceLocation::Current());
	
	private:
		
		TFUniquePtr<WGenericFile> m_pFile;
		
		uint64 count;
		
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
