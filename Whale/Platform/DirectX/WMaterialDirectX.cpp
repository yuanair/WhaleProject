//
// Created by admin on 2024/7/25.
//

#include "WMaterialDirectX.hpp"

namespace Whale::DirectX
{
	Bool WMaterialDirectX::IsGPUResourceCreated() const noexcept
	{
		return true;
	}
	
	void WMaterialDirectX::Create(const WMaterialArg &arg) noexcept
	{
	
	}
	
	
	void WMaterialDirectX::OnUse() const noexcept
	{
		for (auto &pWeak: GetPBitmaps())
		{
			auto pBitmap = pWeak.Lock();
			if (!pBitmap || !pBitmap->IsEnabled()) continue;
			pBitmap->Use();
		}
	}
	
	void WMaterialDirectX::OnEnable() noexcept
	{
	
	}
	
	void WMaterialDirectX::OnDisable() noexcept
	{
	
	}
	
	void WMaterialDirectX::OnResourceDestroy() noexcept
	{
	
	}
} // Whale