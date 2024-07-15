//
// Created by admin on 2024/7/9.
//

#pragma once

#include "Whale/Core/FUndefinedData.hpp"
#include "Whale/DirectX/FDirectXHeader.hpp"

namespace Whale
{
	class WShaderDirectX12Data : public WObject
	{
	public:
		
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pID3D12PipelineState;
		
	};
}