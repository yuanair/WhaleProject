//
// Created by admin on 2024/7/25.
//

#pragma once

#include "Whale/Tool/Core.hpp"

namespace Whale::Tool
{
	
	///
	/// 启用禁用接口
	class WHALE_API IEnable
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
		
		/// 是否已启用（不可重载）
		[[nodiscard]] Bool GetEnabled() const noexcept { return m_enable; }
		
		/// 是否已启用（可重载）
		[[nodiscard]] virtual Bool IsEnabled() const noexcept { return m_enable; }
	
	private:
		
		virtual void OnEnable() noexcept = 0;
		
		virtual void OnDisable() noexcept = 0;
	
	private:
		
		Bool m_enable = false;
		
	};
	
} // Whale
