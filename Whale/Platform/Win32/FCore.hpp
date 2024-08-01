//
// Created by admin on 2024/7/1.
//

#pragma once

#include "HWinDef.hpp"
#include "Whale/Core/Container/TFString.hpp"
#include "FResult.hpp"

namespace Whale::Win32
{
	// Win32核心功能
	class WHALE_API FCore
	{
	public:
		
		//
		// 运行命令
		//
		template<class ElemT, class String = Container::TFString<ElemT>>
		static HInstance ShellExecuteT(
			HWindow hWindow, const String &operation, const String &file, const String &parameters,
			const String &directory, int32 showCmd
		);
		
		///
		/// 退出消息循环
		/// \param result 返回值
		static void Exit(int32 result);
		
		///
		/// \return 是否以管理员模式运行
		static Bool IsRunAsAdministrator();
		
		///
		/// 以管理员权限启动应用
		/// \param strApp 模块文件名
		template<class ElemT>
		static Bool GainAdminPrivileges(const Container::TFString<ElemT> &strApp);
		
		///
		/// \return
		template<class ElemT>
		static int32 GetCommandShow();
		
		/// 命令行
		template<class ElemT>
		static Container::TFString<ElemT> GetCommandLineT();
		
		/// 应用实例
		template<class ElemT>
		static HInstance GetInstance();
		
		///
		/// \param id 图标资源ID
		/// \return 图标
		template<class ElemT>
		static HIcon GetIcon(int32 id) { return GetIcon<ElemT>(id, GetInstance<ElemT>()); }
		
		///
		/// \param id 图标资源ID
		/// \param hInstance 应用实例
		/// \return 图标
		template<class ElemT>
		static HIcon GetIcon(int32 id, HInstance hInstance);
		
		///
		/// \param id 光标资源ID
		/// \return 光标
		template<class ElemT>
		static HCursor GetCursor(int32 id) { return GetCursor<ElemT>(id, GetInstance<ElemT>()); }
		
		///
		/// \param id 光标资源ID
		/// \param hInstance 应用实例
		/// \return 光标
		template<class ElemT>
		static HCursor GetCursor(int32 id, HInstance hInstance);
		
		///
		/// \return 获取最后的WIN32错误
		static FResult GetLastError();
		
		///
		/// windows错误信息
		template<class ElemT>
		static Container::TFString<ElemT> MessageToString(HResult dwMessageId);
		
		
	};
	
	
} // Whale
