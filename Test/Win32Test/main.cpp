﻿#include "Whale/Core/Debug/FDebug.hpp"
#include "Whale/Core/Object/WProgram.hpp"
#include "Whale/Render/Win32/WWindow.hpp"
#include "Whale/Render/Utility/WRenderer.hpp"
#include "Whale/Language/Json/TFValue.hpp"

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
	
	void OnTick(float deltaTIme) override;
	
	Win32::LResult OnDestroy() override
	{
		Win32::FCore::Exit();
		return WWindow::OnDestroy();
	}

public:
	
	class Program &program;
	
	[[nodiscard]]auto &GetPRenderTarget() const { return pRenderTarget; }

private:
	
	TFSharedPtr<WWindowRenderTarget> pRenderTarget;
	
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

protected:
	
	void OnTick(float deltaTIme) override
	{
		Win32::WWindow::OnTick(deltaTIme);
	}

public:
	
	class Program &program;
	
	[[nodiscard]]auto &GetPRenderTarget() const { return pRenderTarget; }

private:
	
	TFSharedPtr<WWindowRenderTarget> pRenderTarget;
	
};

class Program : public WProgram
{
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
		} windowData;
		StringA shader;
	} data;
	
	TFUniquePtr<MyWindow> pWindow;
	
	TFUniquePtr<MyWindow2> pWindow2;
	
	TFUniquePtr<Win32::WWindow::WWindowClass> pWindowClass;
	
	TFUniquePtr<WRenderer> pRender;
	
	TFSharedPtr<WShader> pShader;
	
	TFSharedPtr<WStaticMesh> pMesh;

public:
	
	[[nodiscard]]auto &GetData() const { return data; }
	
	[[nodiscard]]auto &GetPWindow() const { return pWindow; }
	
	[[nodiscard]]auto &GetPWindowClass() const { return pWindowClass; }
	
	[[nodiscard]]auto &GetPRender() const { return pRender; }
	
	[[nodiscard]]auto &GetPShader() const { return pShader; }
	
	[[nodiscard]]auto &GetPMesh() const { return pMesh; }
	
};

void Program::InitData()
{
	Language::Json::JsonT testValue;
	testValue = true;
	testValue = 578;
	testValue = 3.14159;
	testValue = WHALE_TEXT("Hello Json");
	testValue = {
		Language::Json::JsonT{1.0},
		Language::Json::JsonT{5},
		Language::Json::JsonT{10}
	};
	
	testValue["Hi"] = "Hello";
	testValue["100"] = "800";
	
	std::ifstream dataFile{"./Data/data.json"};
	if (!dataFile.is_open())
	{
		throw FFileNotFoundException("cannot to open \"./Data/data.json\"");
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
	this->data.toEncoding = dataObject["toEncoding"].as_string().c_str();
	this->data.fromEncoding = dataObject["fromEncoding"].as_string().c_str();
	this->data.windowData.name = dataObject["windowData"].as_object()["name"].as_string().c_str();
	this->data.windowData.name = WLocale::Between(
		this->data.windowData.name, this->data.toEncoding, this->data.fromEncoding
	);
	this->data.shader = dataObject["shader"].as_string().c_str();
	
	pWindowClass = MakeUnique<Win32::WWindow::WWindowClass>(
		Win32::FCore::GetInstance(), WHALE_TEXT("WhaleTestWindowClass")
	);
	if (!pWindowClass->Register())
	{
		throw FException((
			                 "Register Window Class Failed!\r\nError: " +
			                 Win32::FCore::MessageToStringA(Win32::FCore::GetLastError())).c_str()
		);
	}
	
	pWindow = MakeUnique<MyWindow>(*this);
	pWindow->Create(*pWindowClass, WLocale::AToTString(this->data.windowData.name, this->data.toEncoding));
	auto buffer = pWindow->GetNameA();
	
	if (pWindow->GetHWindow().handle == nullptr)
	{
		throw FException((
			                 "Create Window Failed!\r\nError: " +
			                 Win32::FCore::MessageToStringA(Win32::FCore::GetLastError())).c_str()
		);
	}
	pWindow->ShowAndUpdate();
	
	
	pWindow2 = MakeUnique<MyWindow2>(*this);
	pWindow2->Create(*pWindowClass, WLocale::AToTString(this->data.windowData.name, this->data.toEncoding));
	if (pWindow2->GetHWindow().handle == nullptr)
	{
		throw FException((
			                 "Create Window Failed!\r\nError: " +
			                 Win32::FCore::MessageToStringA(Win32::FCore::GetLastError())).c_str()
		);
	}
	pWindow2->ShowAndUpdate();
	
	
}

void Program::InitDirectX()
{
	pRender = WRenderer::CreateRenderer(ERendererTypeDirectX);
	pShader = pRender->CreateShader();
	pMesh = pRender->CreateStaticMesh();
	pRender->Create();
	pShader->CreateFromFile(WLocale::ToUTFString(data.shader, data.fromEncoding));
	pMesh->SetVertexes(
		{
			FVertex{{0.0f, 0.25f, 0.0f, 1.0f},
			        {1.0f, 0.0f,  0.0f, 1.0f}},
			FVertex{{0.25f, -0.25f, 0.0f, 1.0f},
			        {0.0f,  1.0f,   0.0f, 1.0f}},
			FVertex{{-0.25f, -0.25f, 0.0f, 1.0f},
			        {0.0f,   0.0f,   1.0f, 1.0f}}
		}
	);
	pMesh->SetPShader({pShader});
	pMesh->Load();
	
	pWindow->InitDirectX();
	pWindow2->InitDirectX();
	
	
	pRender->renderTargets.emplace_back(pWindow->GetPRenderTarget());
	pRender->renderTargets.emplace_back(pWindow2->GetPRenderTarget());
	
	pWindow->GetPRenderTarget()->renderObjects.emplace_back(pMesh);
}

void MyWindow::InitDirectX()
{
	
	pRenderTarget = program.GetPRender()->CreateWindowRenderTarget();
	pRenderTarget->Create(*this);
}

void MyWindow2::InitDirectX()
{
	pRenderTarget = program.GetPRender()->CreateWindowRenderTarget();
	pRenderTarget->Create(*this);
}

void MyWindow::OnTick(float deltaTIme)
{
	WWindow::OnTick(deltaTIme);
}


int main()
{
	FDebug::LogToFile(".\\logs\\%Y%m%d.log");
	return Program().WHALE_T(Run)();
}

#include "Whale/Render/Win32/FWinMain.hpp"
//*/

