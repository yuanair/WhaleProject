//
// Created by admin on 2024/8/2.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>

namespace Whale
{
	
	/// 创建窗口类参数
	struct WHALE_API FWindowClassCreateArg
	{
		/// 名称（多个窗口类不可重名）
		FString m_name;
	};
	
	/// 窗口类
	class WHALE_API WGenericWindowClass : public WObject
	{
	public:
		
		WGenericWindowClass() = default;
		
		WGenericWindowClass(const WGenericWindowClass &) = delete;
	
	public:
		
		WGenericWindowClass &operator=(const WGenericWindowClass &) = delete;
	
	public:
		
		/// 创建
		virtual Bool Create(const FWindowClassCreateArg &arg) = 0;
		
		/// 获取名称
		[[nodiscard]] const FString &GetName() const { return m_name; }
	
	protected:
		
		FString m_name;
		
	};
	
} // Whale
