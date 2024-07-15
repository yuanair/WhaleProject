//
// Created by admin on 2024/7/12.
//

#pragma once

#include "Whale/Core/WObject.hpp"

namespace Whale
{
	///
	/// 渲染对象
	class WHALE_API WRenderObject : public WObject
	{
	public:
		
		virtual void OnRender() = 0;
		
	};
	
} // Whale
