//
// Created by admin on 2024/7/25.
//

#pragma once


#include "Whale/Platform/WRenderingPipeline.hpp"
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
		
		[[nodiscard]] Bool IsGPUResourceCreated() const noexcept override;
	
	private:
		
		void OnGPUCreate(const WRenderingPipelineArg &arg) noexcept override;
		
		void OnGPUDestroy() noexcept override;
		
		void OnUse() noexcept override;
		
		void OnEnable() noexcept override;
		
		void OnDisable() noexcept override;
	
	private:
		
		WRendererDirectX *m_pRenderer;
		
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pID3D12PipelineState;
		
	};
	
} // Whale
