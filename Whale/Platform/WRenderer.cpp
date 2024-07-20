//
// Created by admin on 2024/7/9.
//

#include "WRenderer.hpp"

#include "Whale/Platform/DirectX/WRendererDirectX.hpp"
#include "Whale/Platform/OpenGL/WRendererOpenGL.hpp"

namespace Whale
{
	
	WRenderer::WRenderer()
	{
		if (pRenderer != nullptr)
		{
			throw;
		}
		pRenderer = this;
	}
	
	WRenderer::~WRenderer()
	{
		pRenderer = nullptr;
	}
	
	TFUniquePtr<WRenderer> WRenderer::CreateRenderer(ERendererType type)
	{
		switch (type)
		{
			case ERendererTypeDirectX:
				FDebug::LogInfo(WhaleTagW, ToStringW(type));
				return MakeUnique<DirectX::WRendererDirectX>();
			case ERendererTypeOpenGL:
				FDebug::LogInfo(WhaleTagW, ToStringW(type));
				return MakeUnique<OpenGL::WRendererOpenGL>();
			default:
				FDebug::LogError(WhaleTagW, ToStringW(type));
				return nullptr;
		}
	}
	
	WRenderer *WRenderer::pRenderer = nullptr;
	
	StringA WRenderer::ToStringA(ERendererType type)
	{
		switch (type)
		{
			case ERendererTypeNone:
				return "None";
			case ERendererTypeDirectX:
				return "DirectX";
			case ERendererTypeOpenGL:
				return "OpenGL";
			default:
				return "<unknown-type>";
		}
	}
	
	StringW WRenderer::ToStringW(ERendererType type)
	{
		switch (type)
		{
			case ERendererTypeNone:
				return L"None";
			case ERendererTypeDirectX:
				return L"DirectX";
			case ERendererTypeOpenGL:
				return L"OpenGL";
			default:
				return L"<unknown-type>";
		}
	}
	
	
} // Whale