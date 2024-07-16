//
// Created by admin on 2024/7/9.
//

#include "WRenderer.hpp"

#include "Whale/Render/DirectX/WRendererDirectX.hpp"
#include "Whale/Render/OpenGL/WRendererOpenGL.hpp"

namespace Whale
{
	
	WRenderer::WRenderer()
	{
		if (pRenderer != nullptr)
		{
			FDebug::Fatal(WProgram::GetAppNameW(), L"Multiple renderers were created!");
			throw;
		}
		pRenderer = this;
	}
	
	WRenderer::~WRenderer()
	{
		pRenderer = nullptr;
	}
	
	FTUniquePtr<WRenderer> WRenderer::CreateRenderer(ERendererType type)
	{
		switch (type)
		{
			case ERendererTypeDirectX:
				FDebug::LogInfo(WProgram::GetAppNameW(), ToStringW(type));
				return MakeUnique<WRendererDirectX>();
			case ERendererTypeOpenGL:
				FDebug::LogInfo(WProgram::GetAppNameW(), ToStringW(type));
				return MakeUnique<WRendererOpenGL>();
			default:
				FDebug::LogError(WProgram::GetAppNameW(), ToStringW(type));
				return nullptr;
		}
	}
	
	WRenderer *WRenderer::pRenderer = nullptr;
	
	FTStringA WRenderer::ToStringA(ERendererType type)
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
	
	FTStringW WRenderer::ToStringW(ERendererType type)
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