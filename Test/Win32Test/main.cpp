#include <Whale/FDebug.hpp>
#include <Whale/WProgram.hpp>
#include <Whale/WRenderer.hpp>
#include <Whale/WShader.hpp>
#include <Whale/WStaticMesh.hpp>
#include <Whale/WWindowRenderTarget.hpp>
#include <Whale/IO.hpp>
#include <Whale/Json/TFValue.hpp>
#include <Whale/FApplication.hpp>

#include <Whale/Win32/WWindow.hpp>
#include <Whale/Win32/WDragQueryFileReader.hpp>
#include <Whale/Win32/FMessageBox.hpp>
#include <Whale/Win32/FPE.hpp>
#include <Whale/Win32/FFile.hpp>

#include <boost/json.hpp>

#include "./Resources/Resources.h"

using namespace Whale;

class MyWindow
{
public:
	
	MyWindow()
	{
		//this->bEnableOnChar = true;
		//this->bEnableOnString = true;
		pWindow = MakeUnique<Win32::WWindow>();
	}

protected:
	
	void OnCreate()
	{
		pWindow->EnableFileDrag();
	}
	
	void OnDropFiles(Win32::HDrop hDropInfo);
	
	static void OnDestroy()
	{
		FApplication::Exit();
	}

public:
	
	[[nodiscard]]
	auto &GetPRenderTarget() const noexcept { return pRenderTarget; }

public:
	
	TFWeakPtr<WWindowRenderTarget> pRenderTarget;
	
	TFUniquePtr<WWindow> pWindow;
	
	void ShowPE(const StringW &fileName) const;
};

class Program : public WProgram
{
public:
	
	Program() : dataDirectoryA("./" CMAKE_PROJECT_NAME "Data"), dataDirectoryW(L"./" CMAKE_PROJECT_NAME "Data")
	{
	}
	
	~Program()
	{
	
	}

public:
	
	const StringA                             dataDirectoryA;
	const StringW                             dataDirectoryW;

public:
	
	void InitData();
	
	void InitDirectX();

protected:
	
	void OnBeginPlay() override
	{
		WProgram::OnBeginPlay();
		InitData();
		InitDirectX();
	}
	
	void OnTick(Float deltaTime) override
	{
		WProgram::OnTick(deltaTime);
		window.pWindow->Tick(deltaTime);
		window2.pWindow->Tick(deltaTime);
		pRender->Render();
	}
	
	void OnEndPlay() override
	{
		WProgram::OnEndPlay();
	}


private:
	
	struct Data
	{
		StringA toEncoding;
		StringA fromEncoding;
		struct WindowData
		{
			StringA name;
		}       windowData;
		StringA shader;
	}                                         data;
	MyWindow                                  window;
	MyWindow                                  window2;
	TFUniquePtr<Win32::WWindow::WWindowClass> pWindowClass;
	TFUniquePtr<WRenderer>                    pRender;
	TFWeakPtr<WShader>                        pVertexShader;
	TFWeakPtr<WShader>                        pPixelShader;
	TFWeakPtr<WRenderingPipeline>             pRenderingPipeline;
	TFWeakPtr<WMaterial>                      pMaterial;
	TFWeakPtr<WStaticMesh>                    pMesh;
	TFWeakPtr<WBitmap>                        pBitmap;

public:
	
	[[nodiscard]]auto &GetData() const { return data; }
	
	[[nodiscard]]auto &GetWindow() const { return window; }
	
	[[nodiscard]]auto &GetPWindowClass() const { return pWindowClass; }
	
	[[nodiscard]]auto &GetPRender() const { return pRender; }
	
	[[nodiscard]]auto &GetPMesh() const { return pMesh; }
	
	[[nodiscard]]auto &GetPBitmap() const { return pBitmap; }
	
	[[nodiscard]]auto &GetPBitmap() { return pBitmap; }
	
};

void Program::InitData()
{
	
	this->data.toEncoding      = "GBK";
	this->data.fromEncoding    = "UTF-8";
	this->data.windowData.name = "鲸鱼测试";
	this->data.windowData.name = FLocale::Between(
		this->data.windowData.name, this->data.toEncoding, this->data.fromEncoding
	);
	this->data.shader          = dataDirectoryA + "/test.hlsl";
	
	pWindowClass = MakeUnique<Win32::WWindow::WWindowClass>(
		Win32::FCore::GetInstance<CharT>(), WHALE_TEXT("WhaleTestWindowClass")
	);
	if (!pWindowClass->Register(
		Win32::FCore::GetIcon<CharT>(IDI_APP_ICON), Win32::FCore::GetIcon<CharT>(IDI_APP_ICON_SM)))
	{
		Win32::FCore::GetLastError();
	}
	
	window.pWindow = MakeUnique<Win32::WWindow>();
	((Win32::WWindow *) window.pWindow.GetPtr())->Create(
		*pWindowClass, FLocale::AToTString(
			this->data.windowData.name, this->data.toEncoding
		));
	
	if (window.pWindow->GetHWindow().handle == nullptr)
	{
		Win32::FCore::GetLastError();
	}
	window.pWindow->ShowAndUpdate();
	
	
	window2.pWindow = MakeUnique<Win32::WWindow>();
	((Win32::WWindow *) window.pWindow.GetPtr())->Create(
		*pWindowClass, FLocale::AToTString(
			this->data.windowData.name, this->data.toEncoding
		));
	if (window2.pWindow->GetHWindow().handle == nullptr)
	{
		Win32::FCore::GetLastError();
	}
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
			.m_fileName=FLocale::ToUTFString(data.shader, data.fromEncoding),
			.m_type=EShaderTypeVertex,
			.entryPoint="vertex"
		}
	);
	pPixelShader.Lock()->CreateFromFile(
		{
			.m_fileName=FLocale::ToUTFString(data.shader, data.fromEncoding),
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
	
	window.pRenderTarget = pRender->MakeWindowRenderTarget();
	window.pRenderTarget.Lock()->Create({.m_window=*window.pWindow, .m_frameBackBufferCount=3});
	window.pRenderTarget.Lock()->Enable();
	window2.pRenderTarget = pRender->MakeWindowRenderTarget();
	window2.pRenderTarget.Lock()->Create({.m_window=*window.pWindow, .m_frameBackBufferCount=3});
	window2.pRenderTarget.Lock()->Enable();
	window.GetPRenderTarget().Lock()->m_renderObjects.Append(pMesh);
}

//Win32::LResult MyWindow::OnDropFiles(Win32::HDrop hDropInfo)
//{
//	Win32::WDragQueryFileReader reader;
//	StringW                     fileName = L"";
//	reader.Init<CharW>(hDropInfo);
//	for (uint32 index   = 0; index < reader.GetFileCount(); index++)
//	{
//		reader.Get<CharW>(fileName, index);
//	}
//	if (auto    pBitmap = program.GetPBitmap().Lock())
//	{
//		// ShowPE(fileName);
//		try
//		{
//			pBitmap->CreateFromFile({.m_fileName=fileName});
//		}
//		catch (Win32::FResultException &e)
//		{
//			Win32::FMessageBox::Show(e.What(), program.GetData().windowData.name);
//		}
//	}
//	return false;
//}


int WhaleMain()
{
	FDebug::LogToFile(".\\logs\\%Y%m%d.log");
	Bool isRunAsAdministrator = FApplication::IsRunAsAdministrator();
	FDebug::Log(
		WHALE_TEXT("IsRunAsAdministrator"),
		isRunAsAdministrator ? WHALE_TEXT("true") : WHALE_TEXT("false"),
		isRunAsAdministrator ? Info : Fatal
	);
	return Program().Run(WHALE_TEXT(""));
}

#include <Whale/WhaleMain.hpp>

#include <ImageHlp.h>

void MyWindow::ShowPE(const StringW &fileName) const
{
	Win32::FPE pe;
	pe.LoadFromFile<CharT>(Win32::FFile::OpenReadOnly(fileName));
	PIMAGE_DOS_HEADER      pDH  = nullptr;//指向IMAGE_DOS结构的指针
	PIMAGE_NT_HEADERS      pNtH = nullptr;//指向IMAGE_NT结构的指针
	PIMAGE_FILE_HEADER     pFH  = nullptr;//指向IMAGE_FILE结构的指针
	PIMAGE_OPTIONAL_HEADER pOH  = nullptr;//指向IMAGE_OPTIONALE结构的指针
	pDH = (PIMAGE_DOS_HEADER) pe.GetImageBase().handle;
	if (pDH->e_magic != IMAGE_DOS_SIGNATURE) //判断是否为MZ
	{
		FDebug::LogError("", "Not a valid PE file!");
		return;
	}
	pNtH = (PIMAGE_NT_HEADERS) ((ULONG_PTR) pDH + pDH->e_lfanew); //判断是否为PE格式
	if (pNtH->Signature != IMAGE_NT_SIGNATURE)
	{
		FDebug::LogError("", "Not a valid PE file!");
		return;
	}
}

//*/

