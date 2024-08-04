﻿#include <Whale/FDebug.hpp>
#include <Whale/WProgram.hpp>
#include <Whale/WRenderer.hpp>
#include <Whale/WShader.hpp>
#include <Whale/WStaticMesh.hpp>
#include <Whale/WWindowRenderTarget.hpp>
#include <Whale/IO.hpp>
#include <Whale/Json/TFValue.hpp>

#include <Whale/FPlatformManager.hpp>
#include <Whale/WGenericWindowManager.hpp>

#include <Whale/Windows/WDragQueryFileReader.hpp>
#include <Whale/Windows/FMessageBox.hpp>
#include <Whale/Windows/FPE.hpp>

#include "./Resources/Resources.h"

using namespace Whale;

class MyWindow
{
public:
	
	MyWindow()
	{
		//this->bEnableOnChar = true;
		//this->bEnableOnString = true;
		pWindow = FPlatformManager::Get().GetPlatform().GetWindowManager().NewWindow();
		pWindow->m_inputSystem.onDrop += OnDropFiles;
	}
	
	static void OnDestroy(const ActionEventArg &arg);

protected:
	
	void OnCreate(const ActionEventArg &arg)
	{
		pWindow->EnableFileDrag();
	}
	
	static void OnDropFiles(HDrop hDrop);

public:
	
	[[nodiscard]]
	auto &GetPRenderTarget() const noexcept { return pRenderTarget; }

public:
	
	TFWeakPtr<WWindowRenderTarget> pRenderTarget;
	
	WGenericWindow *pWindow;
	
	void ShowPE(const StringW &fileName) const;
};

class Program : public WProgram
{
public:
	
	Program() : WProgram(FPlatformManager::Get().GetPlatform().NewTimer()),
	            dataDirectoryA("./" CMAKE_PROJECT_NAME "Data"),
	            dataDirectoryW(L"./" CMAKE_PROJECT_NAME "Data")
	{
	}
	
	~Program() override = default;

public:
	
	const StringA                 dataDirectoryA;
	const StringW                 dataDirectoryW;

public:
	
	void InitData();
	
	void InitDirectX();

protected:
	
	void OnBeginPlay() override
	{
		WProgram::OnBeginPlay();
		Bool isRunAsAdministrator = FPlatformManager::Get().GetPlatform().IsRunAsAdministrator();
		FDebug::Log<CharT>(
			isRunAsAdministrator ? Info : Fatal,
			WTEXT("IsRunAsAdministrator"),
			isRunAsAdministrator ? WTEXT("true") : WTEXT("false")
		);
		InitData();
		InitDirectX();
	}
	
	void OnTick(Double deltaTime) override
	{
		WProgram::OnTick(deltaTime);
		pRender->Render();
	}
	
	void OnEndPlay() override
	{
		WProgram::OnEndPlay();
		pRender->ResourceDestroy();
		FPlatformManager::Get().GetPlatform().GetWindowManager().DeleteWindow(window.pWindow);
		FPlatformManager::Get().GetPlatform().GetWindowManager().DeleteWindow(window2.pWindow);
		FPlatformManager::Get().GetPlatform().GetWindowManager().DeleteWindowClass(pWindowClass);
	}


private:
	
	struct Data
	{
		FString toEncoding;
		FString fromEncoding;
		struct WindowData
		{
			StringA name;
		}       windowData;
		StringA shader;
	}                             data;
	MyWindow                      window;
	MyWindow                      window2;
	TFUniquePtr<WRenderer>        pRender;
	TFWeakPtr<WShader>            pVertexShader;
	TFWeakPtr<WShader>            pPixelShader;
	TFWeakPtr<WRenderingPipeline> pRenderingPipeline;
	TFWeakPtr<WMaterial>          pMaterial;
	TFWeakPtr<WStaticMesh>        pMesh;
	TFWeakPtr<WBitmap>            pBitmap;
	WGenericWindowClass           *pWindowClass;

public:
	
	[[nodiscard]]auto &GetData() const { return data; }
	
	[[nodiscard]]auto &GetWindow() const { return window; }
	
	[[nodiscard]]auto &GetPWindowClass() const { return pWindowClass; }
	
	[[nodiscard]]auto &GetPRender() const { return pRender; }
	
	[[nodiscard]]auto &GetPMesh() const { return pMesh; }
	
	[[nodiscard]]auto &GetPBitmap() const { return pBitmap; }
	
	[[nodiscard]]auto &GetPBitmap() { return pBitmap; }
	
};

static Program &GetProgram()
{
	static Program program;
	return program;
}

void Program::InitData()
{
	
	this->data.toEncoding      = WTEXT("GBK");
	this->data.fromEncoding    = WTEXT("UTF-8");
	this->data.windowData.name = "鲸鱼测试";
	this->data.windowData.name = FPlatformManager::Get().GetLocale().Between(
		this->data.windowData.name, this->data.toEncoding, this->data.fromEncoding
	);
	this->data.shader          = dataDirectoryA + "/test.hlsl";
	
	pWindowClass = FPlatformManager::Get().GetPlatform().GetWindowManager().NewWindowClass();
	pWindowClass->Create({.m_name = WTEXT("WhaleTestWindowClass")});
	
	window.pWindow->Create(
		{
			.m_name = FPlatformManager::Get().GetLocale().ToFString(
				this->data.windowData.name, this->data.toEncoding
			), .m_class = pWindowClass
		}
	);
	
	
	window2.pWindow->Create(
		{
			.m_name = FPlatformManager::Get().GetLocale().ToFString(
				this->data.windowData.name, this->data.toEncoding
			), .m_class = pWindowClass
		}
	);
	window.pWindow->ShowAndUpdate();
	window2.pWindow->ShowAndUpdate();
	
	
}

void Program::InitDirectX()
{
	pRender            = WRenderer::CreateRenderer(ERendererTypeDirectX);
	pVertexShader      = pRender->MakeShader();
	pPixelShader       = pRender->MakeShader();
	pRenderingPipeline = pRender->MakeRenderingPipeline();
	pMaterial          = pRender->MakeMaterial();
	pMesh              = pRender->MakeStaticMesh();
	pBitmap            = pRender->MakeBitmap();
	
	pRender->Init();
	pRender->Enable();
	
	pVertexShader.Lock()->CreateFromFile(
		{
			.m_fileName=FPlatformManager::Get().GetLocale().ToFString(data.shader, data.fromEncoding),
			.m_type=EShaderTypeVertex,
			.entryPoint="vertex"
		}
	);
	pPixelShader.Lock()->CreateFromFile(
		{
			.m_fileName=FPlatformManager::Get().GetLocale().ToFString(data.shader, data.fromEncoding),
			.m_type=EShaderTypePixel,
			.entryPoint="pixel"
		}
	);
	
	pRenderingPipeline.Lock()->CreateFromShader({.m_pVertexShader=pVertexShader, .m_pPixelShader=pPixelShader});
	pRenderingPipeline.Lock()->Enable();
	
	pBitmap.Lock()->CreateFromFile({.m_fileName=dataDirectoryW + L"/1.png"});
	pBitmap.Lock()->Enable();
	
	pMaterial.Lock()->Create({});
	pMaterial.Lock()->Enable();
	pMaterial.Lock()->SetPRenderingPipelines({pRenderingPipeline});
	pMaterial.Lock()->SetPBitmaps({pBitmap});
	
	pMesh.Lock()->SetVertexes
		(
			{
				FVertex{{-0.5f, 0.5f, 0.0f, 1.0f},
				        {1.0f,  0.0f, 0.0f, 1.0f},
				        {0.0f,  0.0f, 0.0f},
				        {0.0f,  1.0f}},
				FVertex{{0.5f, 0.5f, 0.0f, 1.0f},
				        {0.0f, 1.0f, 0.0f, 1.0f},
				        {0.0f, 0.0f, 0.0f},
				        {1.0f, 1.0f}},
				FVertex{{0.5f, -0.5f, 0.0f, 1.0f},
				        {0.0f, 0.0f,  1.0f, 1.0f},
				        {0.0f, 0.0f,  0.0f},
				        {1.0f, 0.0f}},
				FVertex{{-0.5f, 0.5f, 0.0f, 1.0f},
				        {1.0f,  0.0f, 0.0f, 1.0f},
				        {0.0f,  0.0f, 0.0f},
				        {0.0f,  1.0f}},
				FVertex{{0.5f, -0.5f, 0.0f, 1.0f},
				        {0.0f, 0.0f,  1.0f, 1.0f},
				        {0.0f, 0.0f,  0.0f},
				        {1.0f, 0.0f}},
				FVertex{{-0.5f, -0.5f, 0.0f, 1.0f},
				        {0.0f,  0.0f,  1.0f, 1.0f},
				        {0.0f,  0.0f,  0.0f},
				        {0.0f,  0.0f}}
			}
		);
	pMesh.Lock()->SetPMaterials({pMaterial});
	pMesh.Lock()->Create({});
	pMesh.Lock()->Enable();
	
	window.pRenderTarget  = pRender->MakeWindowRenderTarget();
	window.pRenderTarget.Lock()->Create({.m_window=*window.pWindow, .m_frameBackBufferCount=3});
	window.pRenderTarget.Lock()->Enable();
	window.pWindow->m_inputSystem.onDestroy.started += MyWindow::OnDestroy;
	window2.pRenderTarget = pRender->MakeWindowRenderTarget();
	window2.pRenderTarget.Lock()->Create({.m_window=*window2.pWindow, .m_frameBackBufferCount=3});
	window2.pRenderTarget.Lock()->Enable();
	window.GetPRenderTarget().Lock()->m_renderObjects.Append(pMesh);
	window2.GetPRenderTarget().Lock()->m_renderObjects.Append(pMesh);
}

void MyWindow::OnDropFiles(HDrop hDrop)
{
	Windows::WDragQueryFileReader reader;
	StringW                       fileName = L"";
	reader.Init<CharW>(hDrop);
	for (uint32 index   = 0; index < reader.GetFileCount(); index++)
	{
		reader.Get<CharW>(fileName, index);
	}
	if (auto    pBitmap = GetProgram().GetPBitmap().Lock())
	{
		// ShowPE(fileName);
		try
		{
			pBitmap->CreateFromFile({.m_fileName=fileName});
		}
		catch (FResultException &e)
		{
			Windows::FMessageBox::Show(e.What(), GetProgram().GetData().windowData.name);
		}
	}
}


int WhaleMain()
{
	FPlatformManager::Get().GetFileManager().CreateDirectory(WTEXT("./Logs"));
	FDebug::LogToFile(WTEXT("./Logs"), WTEXT("%Y%m%d.log"));
	return FPlatformManager::Get().GetPlatform().Run(GetProgram());
}

#include <Whale/WhaleMain.hpp>

void MyWindow::ShowPE(const StringW &fileName) const
{
	FPE pe;
	pe.LoadFromFile<CharT>(FPlatformManager::Get().GetFileManager().OpenFile(fileName, EFileOpenModeRead));
	PIMAGE_DOS_HEADER      pDH  = nullptr;//指向IMAGE_DOS结构的指针
	PIMAGE_NT_HEADERS      pNtH = nullptr;//指向IMAGE_NT结构的指针
	PIMAGE_FILE_HEADER     pFH  = nullptr;//指向IMAGE_FILE结构的指针
	PIMAGE_OPTIONAL_HEADER pOH  = nullptr;//指向IMAGE_OPTIONALE结构的指针
	pDH = (PIMAGE_DOS_HEADER) pe.GetImageBase().handle;
	if (pDH->e_magic != IMAGE_DOS_SIGNATURE) //判断是否为MZ
	{
		FDebug::Log<CharA>(Error, "", "Not a valid PE file!");
		return;
	}
	pNtH = (PIMAGE_NT_HEADERS) ((ULONG_PTR) pDH + pDH->e_lfanew); //判断是否为PE格式
	if (pNtH->Signature != IMAGE_NT_SIGNATURE)
	{
		FDebug::Log<CharA>(Error, "", "Not a valid PE file!");
		return;
	}
}

void MyWindow::OnDestroy(const ActionEventArg &arg)
{
	FPlatformManager::Get().GetPlatform().Exit(0);
	auto &arrs = GetProgram().GetPRender()->m_pRenderTargets;
//	for (SizeT index = 0; index <= arrs.GetLength(); index++)
//	{
//		if (arrs[index].Get() == G)
//	}

}

//*/

