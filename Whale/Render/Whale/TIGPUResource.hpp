//
// Created by admin on 2024/7/25.
//

#pragma once

#include <Whale/TypeDef.hpp>

namespace Whale
{
	
	
	/// GPU资源
	class WHALE_API TIGPUResource
	{
	public:
		
		/// 启用。
		void Enable() noexcept
		{
			if (m_enable) return;
			m_enable = true;
			OnEnable();
		}
		
		/// 禁用。
		void Disable() noexcept
		{
			if (!m_enable) return;
			m_enable = false;
			OnDisable();
		}
		
		
		/// 释放GPU资源
		void ResourceDestroy() noexcept { OnResourceDestroy(); }
		
		/// 释放GPU资源并禁用
		void GPUDisableAndDisable() noexcept
		{
			OnResourceDestroy();
			Disable();
		}
		
		/// GPU资源是否已创建
		[[nodiscard]] virtual Bool IsGPUResourceCreated() const noexcept = 0;
		
		/// 是否已启用（可重载）
		[[nodiscard]] virtual Bool IsEnabled() const noexcept
		{
			return m_enable && IsGPUResourceCreated();
		}
	
	
	protected:
		
		/// 是否已启用（不可重载）
		[[nodiscard]] Bool GetEnabled() const noexcept { return m_enable; }
	
	private:
		
		virtual void OnEnable() noexcept = 0;
		
		virtual void OnDisable() noexcept = 0;
		
		virtual void OnResourceDestroy() noexcept = 0;
	
	private:
		
		Bool m_enable = false;
		
	};
	
} // Whale
