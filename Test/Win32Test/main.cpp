#include "Whale/Core/FDebug.hpp"
#include "Whale/Platform/WProgram.hpp"
#include "Whale/Platform/Win32/WWindow.hpp"
#include "Whale/Platform/WRenderer.hpp"
#include "Whale/Platform/WShader.hpp"
#include "Whale/Platform/WStaticMesh.hpp"
#include "Whale/Platform/WWindowRenderTarget.hpp"
#include "Whale/Language/Json/TFValue.hpp"

#include "Test/Win32Test/Resources/Resources.h"

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
	
	Win32::LResult OnDestroy() override
	{
		Win32::FCore::Exit();
		return WWindow::OnDestroy();
	}

public:
	
	class Program &program;
	
	[[nodiscard]]
	auto &GetPRenderTarget() const noexcept { return pRenderTarget; }

private:
	
	TFWeakPtr<WWindowRenderTarget> pRenderTarget;
	
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
	
};

void Program::InitData()
{
	
	std::ifstream dataFile{(dataDirectoryA + "/data.json").CStr()};
	if (!dataFile.is_open())
	{
		FDebug::LogFatal(
			WHALE_TEXT("OpenDataJson"),
			FFileNotFoundException(("cannot to open \"" + dataDirectoryA + "/data.json\"").CStr()));
		Win32::FCore::Exit();
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
		Win32::FCore::GetInstance(), WHALE_TEXT("WhaleTestWindowClass")
	);
	if (!pWindowClass->Register(Win32::FCore::GetIcon(IDI_APP_ICON), Win32::FCore::GetIcon(IDI_APP_ICON_SM)))
	{
		throw FException((
			                 "Register Window Class Failed!\r\nError: " +
			                 Win32::FCore::MessageToStringA(Win32::FCore::GetLastError())).CStr()
		);
	}
	
	pWindow = MakeUnique<MyWindow>(*this);
	pWindow->Create(*pWindowClass, FLocale::AToTString(this->data.windowData.name, this->data.toEncoding));
	auto buffer = pWindow->GetNameA();
	
	if (pWindow->GetHWindow().handle == nullptr)
	{
		throw FException((
			                 "Init Window Failed!\r\nError: " +
			                 Win32::FCore::MessageToStringA(Win32::FCore::GetLastError())).CStr()
		);
	}
	pWindow->ShowAndUpdate();
	
	
	pWindow2 = MakeUnique<MyWindow2>(*this);
	pWindow2->Create(*pWindowClass, FLocale::AToTString(this->data.windowData.name, this->data.toEncoding));
	if (pWindow2->GetHWindow().handle == nullptr)
	{
		throw FException((
			                 "Init Window Failed!\r\nError: " +
			                 Win32::FCore::MessageToStringA(Win32::FCore::GetLastError())).CStr()
		);
	}
	pWindow2->ShowAndUpdate();
	
	
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
	
	pBitmap.Lock()->CreateFromFile({.m_fileName=dataDirectoryW + L"/10.jpg", .m_format=DXGI_FORMAT_R32G32B32A32_FLOAT});
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

void MyWindow2::InitDirectX()
{
	pRenderTarget = program.GetPRender()->MakeWindowRenderTarget();
	pRenderTarget.Lock()->Create({.m_window=*this, .m_frameBackBufferCount=2});
	pRenderTarget.Lock()->Enable();
}


int WhaleMain()
{
	FDebug::LogToFile(".\\logs\\%Y%m%d.log");
	Bool isRunAsAdministrator = Win32::FCore::IsRunAsAdministrator();
	FDebug::Log(
		WHALE_TEXT("IsRunAsAdministrator"),
		isRunAsAdministrator ? WHALE_TEXT("true") : WHALE_TEXT("false"),
		isRunAsAdministrator ? Info : Fatal
	);
	return Program().Run(WHALE_TEXT(""));
}

#include "Whale/Platform/WhaleMain.hpp"
//*/

