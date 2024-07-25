//
// Created by admin on 2024/7/13.
//

#pragma once

#include "Whale/Platform/WRenderer.hpp"

namespace Whale::OpenGL
{
	
	///
	/// OpenGL渲染器
	class WHALE_API WRendererOpenGL : public WRenderer
	{
	public:
		
		void OnGPUCreate() noexcept override;
		
		void OnGPUDestroy() noexcept override;
		
		[[nodiscard]] Bool IsGPUResourceCreated() const noexcept override;
	
	private:
		
		void OnRender() override;
		
		void OnEnable() noexcept override;
		
		void OnDisable() noexcept override;
	
	private:
		
		TFUniquePtr<WWindowRenderTarget> OnMakeWindowRenderTarget() override;
		
		TFUniquePtr<WShader> OnMakeShader() override;
		
		TFUniquePtr<WStaticMesh> OnMakeStaticMesh() override;
		
		TFUniquePtr<WBitmap> OnMakeBitmap() override;
	
	public:
		
		[[nodiscard]]
		inline ERendererType GetType() const override { return ERendererTypeOpenGL; }
		
	};
	
} // Whale
