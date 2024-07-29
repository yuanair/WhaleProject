//
// Created by admin on 2024/7/9.
//

#pragma once

#include "Whale/Core/WObject.hpp"
#include "Whale/Core/Memory.hpp"
#include "Whale/Core/Container/TFArray.hpp"
#include "WRenderObject.hpp"
#include "WRenderer.hpp"

namespace Whale
{
	///
	/// 渲染目标
	class WHALE_API WRenderTarget : public WObject, public IEnable
	{
	public:
		
		void Render() { if (IsEnabled()) OnRender(); }
	
	private:
		
		virtual void OnRender() = 0;
	
	public:
		
		Container::TFArray<TFWeakPtr<WRenderObject>> m_renderObjects;
		
	};
	
	
} // Whale
