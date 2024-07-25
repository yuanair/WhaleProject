//
// Created by admin on 2024/7/13.
//

#include "WRendererOpenGL.hpp"

#include "HOpenGLHeader.hpp"

namespace Whale::OpenGL
{
	
	
	TFUniquePtr<WWindowRenderTarget> WRendererOpenGL::OnMakeWindowRenderTarget()
	{
		return nullptr;
		// return MakeUnique<WWindowRenderTargetOpenGL>();
	}
	
	TFUniquePtr<WShader> WRendererOpenGL::OnMakeShader()
	{
		return nullptr;
		// return MakeUnique<WShaderOpenGL>();
	}
	
	TFUniquePtr<WRenderingPipeline> WRendererOpenGL::OnMakeRenderingPipeline()
	{
		return nullptr;
	}
	
	TFUniquePtr<WMaterial> WRendererOpenGL::OnMakeMaterial()
	{
		return nullptr;
	}
	
	TFUniquePtr<WStaticMesh> WRendererOpenGL::OnMakeStaticMesh()
	{
		return nullptr;
		// return MakeUnique<WStaticMeshOpenGL>();
	}
	
	TFUniquePtr<WBitmap> WRendererOpenGL::OnMakeBitmap()
	{
		return nullptr;
		// return TFUniquePtr<WBitmap>();
	}
	
	void WRendererOpenGL::OnRender()
	{
	
	}
	
	void WRendererOpenGL::OnGPUCreate() noexcept
	{
		PIXELFORMATDESCRIPTOR pfd;
		pfd.nSize           = 40;
		pfd.nVersion        = 1;
		//支持绘制到窗口、支持OPENGL、支持GDI
		pfd.dwFlags         = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_SUPPORT_GDI;
		pfd.iPixelType      = PFD_TYPE_RGBA;
		pfd.cColorBits      = 0;
		pfd.cRedBits        = 0;
		pfd.cRedShift       = 0;
		pfd.cGreenBits      = 0;
		pfd.cGreenShift     = 0;
		pfd.cBlueBits       = 0;
		pfd.cBlueShift      = 0;
		pfd.cAlphaBits      = 0;
		pfd.cAlphaShift     = 0;
		pfd.cAccumBits      = 0;
		pfd.cAccumRedBits   = 0;
		pfd.cAccumGreenBits = 0;
		pfd.cAccumBlueBits  = 0;
		pfd.cAccumAlphaBits = 0;
		pfd.cDepthBits      = 0;
		pfd.cStencilBits    = 0;
		pfd.cAuxBuffers     = 0;
		pfd.iLayerType      = PFD_MAIN_PLANE;
		pfd.bReserved       = 0;
		pfd.dwLayerMask     = 0;
		pfd.dwVisibleMask   = 0;
		pfd.dwDamageMask    = 0;
		
		//获取屏幕的设备环境
		HDC hdc         = GetDC(nullptr);
		//选择像素格式
		int pixelFormat = ChoosePixelFormat(hdc, &pfd);
		//设置像素格式
		SetPixelFormat(hdc, pixelFormat, &pfd);
		//创建OpenGL渲染环境
		HGLRC hglrc = wglCreateContext(hdc);
		//为当前线程指定设备环境和渲染环境
		wglMakeCurrent(hdc, hglrc);
		
		if (!gladLoadGL())
		{
			FDebug::LogError(TagA, FLoadException("Failed to initialize GLAD"));
			return;
		}
		glViewport(0, 0, 800, 800);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
	
	void WRendererOpenGL::OnGPUDestroy() noexcept
	{
	
	}
	
	Bool WRendererOpenGL::IsGPUResourceCreated() const noexcept
	{
		return true;
	}
	
	void WRendererOpenGL::OnEnable() noexcept
	{
	
	}
	
	void WRendererOpenGL::OnDisable() noexcept
	{
	
	}
	
} // Whale