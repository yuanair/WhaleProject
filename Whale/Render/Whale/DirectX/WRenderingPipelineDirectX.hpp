//
// Created by admin on 2024/7/25.
//

#pragma once

#include <Whale/WRenderingPipeline.hpp>
#include "HDirectXHeader.hpp"
#include "WRendererDirectX.hpp"

namespace Whale::DirectX
{
	///
	/// DirectX 渲染管线
	class WRenderingPipelineDirectX : public WRenderingPipeline
	{
	public:
		
		explicit WRenderingPipelineDirectX(WRendererDirectX *pRenderer) : m_pRenderer(pRenderer) {}
	
	public:
		
		Bool CreateFromShader(const WRenderingPipelineArg &arg) noexcept override;
		
		[[nodiscard]] Bool IsGPUResourceCreated() const noexcept override;
	
	private:
		
		void OnResourceDestroy() noexcept override;
		
		void OnUse() noexcept override;
		
		void OnEnable() noexcept override;
		
		void OnDisable() noexcept override;
	
	private:
		
		WRendererDirectX *m_pRenderer;
		
		Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pID3D12PipelineState;
		
	};
	
} // Whale
