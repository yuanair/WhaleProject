//
// Created by admin on 2024/7/25.
//

#pragma once

#include "Whale/Platform/WMaterial.hpp"
#include "HDirectXHeader.hpp"
#include "WRendererDirectX.hpp"

namespace Whale::DirectX
{
	
	///
	/// DirectX 材质
	class WHALE_API WMaterialDirectX : public WMaterial
	{
	public:
		
		explicit WMaterialDirectX(WRendererDirectX *pRenderer) : m_pRenderer(pRenderer) {}
	
	public:
		
		[[nodiscard]] Bool IsGPUResourceCreated() const noexcept override;
	
	private:
		void OnGPUCreate(const WMaterialArg &arg) noexcept override;
		
		void OnGPUDestroy() noexcept override;
		
		void OnUse() const noexcept override;
		
		void OnEnable() noexcept override;
		
		void OnDisable() noexcept override;
	
	private:
		
		WRendererDirectX *m_pRenderer;
		
	};
	
} // Whale
