//
// Created by admin on 2024/7/1.
//

#pragma once

#include "FWinDef.hpp"
#include <string>

namespace Whale::Win32
{
	// Win32核心功能
	class WHALE_API FCore
	{
	public:
		
		//
		// 运行命令
		//
		static HInstance ShellExecuteT(
			HWindow hWnd, const std::string &operation, const std::string &file, const std::string &parameters,
			const std::string &directory, int32 showCmd
		);
		
		//
		// 运行命令
		//
		static HInstance ShellExecuteT(
			HWindow hWnd, const std::wstring &operation, const std::wstring &file, const std::wstring &parameters,
			const std::wstring &directory, int32 showCmd
		);
		
		///
		/// 退出消息循环
		/// \param result 返回值
		static void Exit(int32 result = 0);
		
		///
		/// \return 是否以管理员模式运行
		static bool IsRunAsAdministrator();
		
		///
		/// 以管理员权限启动应用
		/// \param strApp 模块文件名
		static void GainAdminPrivileges(const std::string &strApp);
		
		///
		/// 以管理员权限启动应用
		/// \param strApp 模块文件名
		static void GainAdminPrivileges(const std::wstring &strApp);
		
		///
		/// \return
		static int32 GetCommandShow();
		
		///
		/// \return 命令行
		static std::string GetCommandLineA();
		
		///
		/// \return 命令行
		static std::wstring GetCommandLineW();
		
		///
		/// \return 应用实例
		static HInstance GetInstance();
		
		///
		/// \param id 图标资源ID
		/// \return 图标
		static HIcon GetIcon(int32 id);
		
		///
		/// \param id 图标资源ID
		/// \param hInstance 应用实例
		/// \return 图标
		static HIcon GetIcon(int32 id, HInstance hInstance);
		
		///
		/// \param id 光标资源ID
		/// \return 光标
		static HCursor GetCursor(int32 id);
		
		///
		/// \param id 光标资源ID
		/// \param hInstance 应用实例
		/// \return 光标
		static HCursor GetCursor(int32 id, HInstance hInstance);
		
		///
		/// \return 获取最后的WIN32错误
		static uint32 GetLastError();
		
		///
		/// windows错误信息
		static std::string MessageToStringA(uint32 dwMessageId);
		
		///
		/// windows错误信息
		static std::wstring MessageToStringW(uint32 dwMessageId);
		
	};
	
} // Whale
