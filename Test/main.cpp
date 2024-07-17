
#include <Whale/Core/Debug/FDebug.hpp>
#include <Whale/Core/Object/WProgram.hpp>
#include <Whale/Core/Container/FMemory.hpp>
#include <Whale/Render/Win32/WWindow.hpp>
#include <Whale/Render/Utility/WRenderer.hpp>

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
	
	uint64 OnDestroy() override
	{
		Win32::FCore::Exit();
		return WWindow::OnDestroy();
	}

public:
	
	class Program &program;
	
	[[nodiscard]]auto &GetPRenderTarget() const { return pRenderTarget; }

private:
	
	FTSharedPtr<WWindowRenderTarget> pRenderTarget;
	
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
	
	FTSharedPtr<WWindowRenderTarget> pRenderTarget;
	
};

class Program : public WProgram
{
public:
	
	void InitData()
	{
		pWindowClass = MakeUnique<Win32::WWindow::WWindowClass>(
			Win32::FCore::GetInstance(), WHALE_WIDE("WhaleTestWindowClass")
		);
		if (!pWindowClass->Register())
		{
			FDebug::Fatal(
				data.windowData.name, (
					"Register Window Class Failed!\r\nError: " +
					Win32::FCore::MessageToStringA(Win32::FCore::GetLastError())).c_str());
			throw;
		}
		
		pWindow = MakeUnique<MyWindow>(*this);
		pWindow->Create(*pWindowClass, WHALE_WIDE("Whale Test"));
		if (pWindow->GetHWindow().handle == nullptr)
		{
			FDebug::Fatal(
				data.windowData.name, (
					"Create Window Failed!\r\nError: " +
					Win32::FCore::MessageToStringA(Win32::FCore::GetLastError())).c_str());
			throw;
		}
		pWindow->ShowAndUpdate();
		
		pWindow2 = MakeUnique<MyWindow2>(*this);
		pWindow2->Create(*pWindowClass, WHALE_WIDE("Whale Test 2"));
		if (pWindow2->GetHWindow().handle == nullptr)
		{
			FDebug::Fatal(
				data.windowData.name, (
					"Create Window Failed!\r\nError: " +
					Win32::FCore::MessageToStringA(Win32::FCore::GetLastError())).c_str());
			throw;
		}
		pWindow2->ShowAndUpdate();
		
		std::ifstream dataFile{"./Data/data.json"};
		if (!dataFile.is_open())
		{
			FDebug::Fatal(data.windowData.name, "cannot to open \"./Data/data.json\"");
			std::shared_ptr<int> a;
			throw;
		}
		boost::json::object dataObject;
		{
			boost::json::value dataValue = boost::json::parse(dataFile);
			if (!dataValue.is_object())
			{
				FDebug::Fatal(data.windowData.name, "data isn't a [JSON object]");
				throw;
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
		this->pWindow->SetName(this->data.windowData.name);
		this->pWindow2->SetName(this->data.windowData.name);
	}
	
	void InitDirectX()
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
		
		
		pRender->renderTargets.push_back(pWindow->GetPRenderTarget());
		pRender->renderTargets.push_back(pWindow2->GetPRenderTarget());
		
		pWindow->GetPRenderTarget()->renderObjects.push_back(pMesh);
	}

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
		FTStringA toEncoding;
		FTStringA fromEncoding;
		struct WindowData
		{
			FTStringA name;
		} windowData;
		FTStringA shader;
	} data;
	
	FTUniquePtr<MyWindow> pWindow;
	
	FTUniquePtr<MyWindow2> pWindow2;
	
	FTUniquePtr<Win32::WWindow::WWindowClass> pWindowClass;
	
	FTUniquePtr<WRenderer> pRender;
	
	FTSharedPtr<WShader> pShader;
	
	FTSharedPtr<WStaticMesh> pMesh;

public:
	
	[[nodiscard]]auto &GetData() const { return data; }
	
	[[nodiscard]]auto &GetPWindow() const { return pWindow; }
	
	[[nodiscard]]auto &GetPWindowClass() const { return pWindowClass; }
	
	[[nodiscard]]auto &GetPRender() const { return pRender; }
	
	[[nodiscard]]auto &GetPShader() const { return pShader; }
	
	[[nodiscard]]auto &GetPMesh() const { return pMesh; }
	
};

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
	return Program().Run();
}

#include <Whale/Render/Win32/FWinMain.hpp>
//*/

