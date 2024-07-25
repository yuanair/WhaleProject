//
// Created by admin on 2024/7/25.
//

#pragma once

#include "Whale/Core/WObject.hpp"
#include "TIGPUResource.hpp"
#include "WRenderingPipeline.hpp"

namespace Whale
{
	
	///
	/// 材质参数
	struct WHALE_API WMaterialArg
	{
	
	
	};
	
	///
	/// 材质
	class WHALE_API WMaterial : public WObject, public TIGPUResource<const WMaterialArg>
	{
	public:
		
		void Use() const noexcept { if (this->IsEnabled()) OnUse(); }
	
	private:
		
		virtual void OnUse() const noexcept = 0;
	
	public:
		
		[[nodiscard]] auto &GetPRenderingPipelines() const noexcept { return m_pRenderingPipelines; }
		
		void SetPRenderingPipelines(Container::TFArray<TFWeakPtr<WRenderingPipeline>> pRenderingPipelines) noexcept
		{
			m_pRenderingPipelines = Whale::Move(pRenderingPipelines);
		}
	
	private:
		
		Container::TFArray<TFWeakPtr<WRenderingPipeline>> m_pRenderingPipelines;
		
	};
	
} // Whale
