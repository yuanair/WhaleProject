//
// Created by admin on 2024/7/9.
//

#include "WRenderer.hpp"

#include "DirectX/WRendererDirectX.hpp"
#include "OpenGL/WRendererOpenGL.hpp"
#include "WWindowRenderTarget.hpp"
#include "WShader.hpp"
#include "WStaticMesh.hpp"
#include "WBitmap.hpp"

namespace Whale
{
	
	TFUniquePtr<WRenderer> WRenderer::CreateRenderer(ERendererType type)
	{
		switch (type)
		{
			case ERendererTypeDirectX:
				FDebug::Log<Char>(Info, logTag, ToString(type));
				return MakeUnique<DirectX::WRendererDirectX>();
			case ERendererTypeOpenGL:
				FDebug::Log<Char>(Info, logTag, ToString(type));
				return MakeUnique<OpenGL::WRendererOpenGL>();
			default:
				FDebug::Log<Char>(Info, logTag, ToString(type));
				return nullptr;
		}
	}
	
	FString WRenderer::ToString(ERendererType type)
	{
		switch (type)
		{
			case ERendererTypeNone:
				return WTEXT("None");
			case ERendererTypeDirectX:
				return WTEXT("DirectX");
			case ERendererTypeOpenGL:
				return WTEXT("OpenGL");
			default:
				return WTEXT("<unknown-type>");
		}
	}
	
	TFWeakPtr<WWindowRenderTarget> WRenderer::MakeWindowRenderTarget()
	{
		return DynamicPointerCast<WWindowRenderTarget>(m_pRenderTargets.Append(OnMakeWindowRenderTarget()));
	}
	
	TFWeakPtr<WShader> WRenderer::MakeShader()
	{
		return m_pShaders.Append(OnMakeShader());
	}
	
	TFWeakPtr<WRenderingPipeline> WRenderer::MakeRenderingPipeline()
	{
		return m_pRenderingPipelines.Append(OnMakeRenderingPipeline());
	}
	
	TFWeakPtr<WMaterial> WRenderer::MakeMaterial()
	{
		return m_pMaterials.Append(OnMakeMaterial());
	}
	
	TFWeakPtr<WStaticMesh> WRenderer::MakeStaticMesh()
	{
		return m_pStaticMeshes.Append(OnMakeStaticMesh());
	}
	
	TFWeakPtr<WBitmap> WRenderer::MakeBitmap()
	{
		return DynamicPointerCast<WBitmap>(m_pImages.Append(OnMakeBitmap()));
	}
	
	
} // Whale