//
// Created by admin on 2024/7/16.
//

#pragma once

#include "Whale/Platform/WShader.hpp"
#include "HDirectXHeader.hpp"

namespace Whale::DirectX
{
	
	///
	/// DirectX着色器(HLSL)
	class WHALE_API WShaderDirectX : public WShader
	{
	public:
		
		bool CreateFromFile(const StringW &fileName) override;
		
		void Use() override;
	
	private:
		
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pID3D12PipelineState;
		
	};
	
} // Whale
