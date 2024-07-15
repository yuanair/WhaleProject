//
// Created by admin on 2024/7/9.
//

#include "WRenderer.hpp"

#include "Whale/DirectX/WRendererDirectX.hpp"
#include "Whale/OpenGL/WRendererOpenGL.hpp"

namespace Whale
{
	
	WRenderer::WRenderer()
	{
		if (pRenderer != nullptr)
		{
			FDebug::Fatal(L"Multiple renderers were created!");
			throw;
		}
		pRenderer = this;
	}
	
	WRenderer::~WRenderer()
	{
		pRenderer = nullptr;
	}
	
	WRenderer *WRenderer::NewRenderer(Type type)
	{
		switch (type)
		{
			case DirectX:
				FDebug::LogInfo(L"new WRendererDirectX()");
				return new WRendererDirectX();
			case OpenGL:
				FDebug::LogInfo(L"new WRendererOpenGL()");
				return new WRendererOpenGL();
			default:
				FDebug::LogError(L"unknown type");
				return nullptr;
		}
	}
	
	WRenderer *WRenderer::pRenderer = nullptr;
	
	std::string WRenderer::ToStringA(WRenderer::Type type)
	{
		switch (type)
		{
			case None:
				return "None";
			case DirectX:
				return "DirectX";
			case OpenGL:
				return "OpenGL";
			default:
				return "<unknown-type>";
		}
	}
	
	std::wstring WRenderer::ToStringW(WRenderer::Type type)
	{
		switch (type)
		{
			case None:
				return L"None";
			case DirectX:
				return L"DirectX";
			case OpenGL:
				return L"OpenGL";
			default:
				return L"<unknown-type>";
		}
	}
	
	
} // Whale