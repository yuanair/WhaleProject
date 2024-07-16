//
// Created by admin on 2024/7/16.
//

#pragma once

#include "Whale/Render/Utility/WShader.hpp"
#include "Whale/Render/DirectX/FDirectXHeader.hpp"

namespace Whale
{
	
	///
	/// DirectX着色器(HLSL)
	class WHALE_API WShaderDirectX : public WShader
	{
	public:
		
		bool CreateFromFile(const std::wstring &fileName) override;
		
		void Use() override;
	
	private:
		
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pID3D12PipelineState;
		
	};
	
} // Whale
