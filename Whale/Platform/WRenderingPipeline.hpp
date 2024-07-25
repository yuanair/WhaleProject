//
// Created by admin on 2024/7/25.
//

#pragma once

#include "Whale/Core/WObject.hpp"
#include "TIGPUResource.hpp"
#include "WShader.hpp"

namespace Whale
{
	
	/// 渲染管线参数
	struct WHALE_API WRenderingPipelineArg
	{
		/// 顶点着色器
		TFWeakPtr<WShader> m_pVertexShader;
		/// 像素着色器
		TFWeakPtr<WShader> m_pPixelShader;
	};
	
	///
	/// 渲染管线 (OpenGL: Program, DirectX: PipelineState)
	class WHALE_API WRenderingPipeline : public WObject, public TIGPUResource<const WRenderingPipelineArg>
	{
	public:
		
		///
		/// 使用渲染管线
		void Use() noexcept { if (IsEnabled()) OnUse(); }
	
	private:
		
		virtual void OnUse() noexcept = 0;
		
	};
	
} // Whale
