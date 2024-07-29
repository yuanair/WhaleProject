//
// Created by admin on 2024/7/25.
//

#pragma once

#include "Whale/Core/WObject.hpp"
#include "TIGPUResource.hpp"
#include "WRenderingPipeline.hpp"
#include "WBitmap.hpp"

namespace Whale
{
	
	///
	/// 材质参数
	struct WHALE_API WMaterialArg
	{
	
	
	};
	
	///
	/// 材质
	class WHALE_API WMaterial : public WObject, public TIGPUResource
	{
	public:
		
		/// 创建
		virtual void Create(const WMaterialArg &arg) noexcept = 0;
		
		void Use() const noexcept { if (this->IsEnabled()) OnUse(); }
	
	private:
		
		virtual void OnUse() const noexcept = 0;
	
	public:
		
		[[nodiscard]] auto &GetPRenderingPipelines() const noexcept { return m_pRenderingPipelines; }
		
		void SetPRenderingPipelines(Container::TFArray<TFWeakPtr<WRenderingPipeline>> pRenderingPipelines) noexcept
		{
			m_pRenderingPipelines = Whale::Move(pRenderingPipelines);
		}
		
		[[nodiscard]] auto &GetPBitmaps() const noexcept { return m_pBitmaps; }
		
		void SetPBitmaps(Container::TFArray<TFWeakPtr<WBitmap>> pBitmaps) noexcept
		{
			m_pBitmaps = Whale::Move(pBitmaps);
		}
	
	private:
		
		Container::TFArray<TFWeakPtr<WRenderingPipeline>> m_pRenderingPipelines;
		
		Container::TFArray<TFWeakPtr<WBitmap>> m_pBitmaps;
		
	};
	
} // Whale
