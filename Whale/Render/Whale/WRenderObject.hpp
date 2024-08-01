//
// Created by admin on 2024/7/12.
//

#pragma once

#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>
#include "TIGPUResource.hpp"

namespace Whale
{
	///
	/// 渲染对象
	class WHALE_API WRenderObject : public WObject, public TIGPUResource
	{
	public:
		
		void Render() { if (IsEnabled())OnRender(); }
	
	private:
		
		virtual void OnRender() = 0;
		
	};
	
} // Whale
