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
	
	void WMaterialDirectX::OnGPUCreate(const WMaterialArg &arg) noexcept
	{
	
	}
	
	void WMaterialDirectX::OnGPUDestroy() noexcept
	{
	
	}
	
	void WMaterialDirectX::OnUse() const noexcept
	{
		for (auto &pWeak: GetPBitmaps())
		{
			auto pBitmap = pWeak.Lock();
			if (!pBitmap || !pBitmap->IsEnabled()) continue;
		}
	}
	
	void WMaterialDirectX::OnEnable() noexcept
	{
	
	}
	
	void WMaterialDirectX::OnDisable() noexcept
	{
	
	}
} // Whale