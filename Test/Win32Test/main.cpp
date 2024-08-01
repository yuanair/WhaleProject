#include "Whale/Core/FDebug.hpp"
#include "Whale/Platform/WProgram.hpp"
#include "Whale/Platform/Win32/WWindow.hpp"
#include "Whale/Platform/Win32/WDragQueryFileReader.hpp"
#include "Whale/Platform/WRenderer.hpp"
#include "Whale/Platform/WShader.hpp"
#include "Whale/Platform/WStaticMesh.hpp"
#include "Whale/Platform/WWindowRenderTarget.hpp"
#include "Whale/Language/Json/TFValue.hpp"

#include "Test/Win32Test/Resources/Resources.h"
#include "Whale/Platform/Win32/FMessageBox.hpp"
#include "Whale/Platform/FApplication.hpp"
#include "Whale/Platform/Win32/FPE.hpp"
#include "Whale/Platform/Win32/FFile.hpp"

#include <boost/json.hpp>

#include <fstream>

using namespace Whale;

class MyWindow : public Win32::WWindow
{
public:
	
	explicit MyWindow(class Program &program)
		: program(program)
	{
		//this->bEnableOnChar = true;
		//this->bEnableOnString = true;
	}
	
	void InitDirectX();

protected:
	
	Win32::LResult OnCreate() override
	{
		GetFileDragAndDropPermission();
		return false;
	}
	
	Win32::LResult OnDropFiles(Win32::HDrop hDropInfo) override;
	
	Win32::LResult OnDestroy() override
	{
		FApplication::Exit();
		return false;
	}

public:
	
	class Program &program;
	
	[[nodiscard]]
	auto &GetPRenderTarget() const noexcept { return pRenderTarget; }

private:
	
	TFWeakPtr<WWindowRenderTarget> pRenderTarget;
	
	void ShowPE(const StringW &fileName) const;
};

class MyWindow2 : public Win32::WWindow
{
public:
	
	explicit MyWindow2(class Program &program)
		: program(program)
	{
		//this->bEnableOnChar = true;
		//this->bEnableOnString = true;
		
	}
	
	void InitDirectX();

public:
	
	class Program &program;
	
	[[nodiscard]]
	auto &GetPRenderTarget() const noexcept { return pRenderTarget; }

private:
	
	TFWeakPtr<WWindowRenderTarget> pRenderTarget;
	
};

class Program : public WProgram
{
public:
	
	Program() : dataDirectoryA("./" CMAKE_PROJECT_NAME "Data"), dataDirectoryW(L"./" CMAKE_PROJECT_NAME "Data") {}
	
	~Program()
	{
		pRender  = nullptr;
		pWindow2 = nullptr;
		pWindow  = nullptr;
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
		pWindow->Tick(deltaTime);
		pWindow2->Tick(deltaTime);
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
	TFUniquePtr<MyWindow>                     pWindow;
	TFUniquePtr<MyWindow2>                    pWindow2;
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
	
	[[nodiscard]]auto &GetPWindow() const { return pWindow; }
	
	[[nodiscard]]auto &GetPWindowClass() const { return pWindowClass; }
	
	[[nodiscard]]auto &GetPRender() const { return pRender; }
	
	[[nodiscard]]auto &GetPMesh() const { return pMesh; }
	
	[[nodiscard]]auto &GetPBitmap() const { return pBitmap; }
	
	[[nodiscard]]auto &GetPBitmap() { return pBitmap; }
	
};

void Program::InitData()
{
	
	std::ifstream dataFile{(dataDirectoryA + "/data.json").CStr()};
	if (!dataFile.is_open())
	{
		FDebug::LogFatal(
			WHALE_TEXT("OpenDataJson"),
			FFileNotFoundException(("cannot to open \"" + dataDirectoryA + "/data.json\"").CStr()));
		FApplication::Exit();
		return;
	}
	boost::json::object dataObject;
	{
		boost::json::value dataValue = boost::json::parse(dataFile);
		if (!dataValue.is_object())
		{
			throw FInvalidCastException("data isn't a [JSON object]");
		}
		dataObject = dataValue.as_object();
	}
	this->data.toEncoding      = dataObject["toEncoding"].as_string().c_str();
	this->data.fromEncoding    = dataObject["fromEncoding"].as_string().c_str();
	this->data.windowData.name = dataObject["windowData"].as_object()["name"].as_string().c_str();
	this->data.windowData.name = FLocale::Between(
		this->data.windowData.name, this->data.toEncoding, this->data.fromEncoding
	);
	this->data.shader          = dataDirectoryA + dataObject["shader"].as_string().c_str();
	
	pWindowClass = MakeUnique<Win32::WWindow::WWindowClass>(
		Win32::FCore::GetInstance<CharT>(), WHALE_TEXT("WhaleTestWindowClass")
	);
	if (!pWindowClass->Register(
		Win32::FCore::GetIcon<CharT>(IDI_APP_ICON), Win32::FCore::GetIcon<CharT>(IDI_APP_ICON_SM)))
	{
		Win32::FCore::GetLastError();
	}
	
	pWindow = MakeUnique<MyWindow>(*this);
	pWindow->Create(*pWindowClass, FLocale::AToTString(this->data.windowData.name, this->data.toEncoding));
	
	if (pWindow->GetHWindow().handle == nullptr)
	{
		Win32::FCore::GetLastError();
	}
	pWindow->ShowAndUpdate<CharT>();
	
	
	pWindow2 = MakeUnique<MyWindow2>(*this);
	pWindow2->Create(*pWindowClass, FLocale::AToTString(this->data.windowData.name, this->data.toEncoding));
	if (pWindow2->GetHWindow().handle == nullptr)
	{
		Win32::FCore::GetLastError();
	}
	pWindow2->ShowAndUpdate<CharT>();
	
	
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
	
	pWindow->InitDirectX();
	pWindow2->InitDirectX();
	pWindow->GetPRenderTarget().Lock()->m_renderObjects.Append(pMesh);
}

void MyWindow::InitDirectX()
{
	pRenderTarget = program.GetPRender()->MakeWindowRenderTarget();
	pRenderTarget.Lock()->Create({.m_window=*this, .m_frameBackBufferCount=3});
	pRenderTarget.Lock()->Enable();
}

Win32::LResult MyWindow::OnDropFiles(Win32::HDrop hDropInfo)
{
	Win32::WDragQueryFileReader reader;
	StringW                     fileName = L"";
	reader.Init<CharW>(hDropInfo);
	for (uint32 index   = 0; index < reader.GetFileCount(); index++)
	{
		reader.Get<CharW>(fileName, index);
	}
	if (auto    pBitmap = program.GetPBitmap().Lock())
	{
		ShowPE(fileName);
		try
		{
			pBitmap->CreateFromFile({.m_fileName=fileName});
		}
		catch (Win32::FResultException &e)
		{
			Win32::FMessageBox::Show(e.What(), program.GetData().windowData.name);
		}
	}
	return false;
}


void MyWindow2::InitDirectX()
{
	pRenderTarget = program.GetPRender()->MakeWindowRenderTarget();
	pRenderTarget.Lock()->Create({.m_window=*this, .m_frameBackBufferCount=2});
	pRenderTarget.Lock()->Enable();
}


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

#include "Whale/Platform/WhaleMain.hpp"

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
		FDebug::LogError(program.GetData().windowData.name, "Not a valid PE file!");
		return;
	}
	pNtH = (PIMAGE_NT_HEADERS) ((ULONG_PTR) pDH + pDH->e_lfanew); //判断是否为PE格式
	if (pNtH->Signature != IMAGE_NT_SIGNATURE)
	{
		FDebug::LogError(program.GetData().windowData.name, "Not a valid PE file!");
		return;
	}
}

//*/

