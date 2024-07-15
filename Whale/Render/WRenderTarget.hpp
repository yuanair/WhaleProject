//
// Created by admin on 2024/7/9.
//

#pragma once

#include <vector>
#include <memory>

#include "Whale/Core/WObject.hpp"
#include "Whale/Win32/WWindow.hpp"
#include "WRenderObject.hpp"
#include "Whale/Core/FUndefinedData.hpp"

namespace Whale
{
	///
	/// 渲染目标
	class WHALE_API WRenderTarget : public WObject
	{
	public:
		
		virtual void OnRender() = 0;
	
	public:
		
		std::vector<std::weak_ptr<WRenderObject>> renderObjects;
		
	};
	
	///
	/// 窗口渲染目标
	class WHALE_API WWindowRenderTarget : public WRenderTarget
	{
	public:
		
		///
		/// 创建
		/// \param window 渲染窗口
		virtual void Create(const Win32::WWindow &window) = 0;
		
	};
	
	///
	/// 窗口渲染目标
	class WHALE_API WWindowRenderTargetDirectX : public WWindowRenderTarget
	{
	public:
		
		WWindowRenderTargetDirectX();
	
	public:
		
		///
		/// 创建
		/// \param window 渲染窗口
		void Create(const Win32::WWindow &window) override;
	
	public:
		
		[[nodiscard]]
		inline const FUndefinedData<class WWindowRenderTargetDirectX12Data> &GetData() const { return data; }
	
	protected:
		
		void OnRender() override;
	
	private:
		
		FUndefinedData<class WWindowRenderTargetDirectX12Data> data;
		
	};
	
} // Whale
