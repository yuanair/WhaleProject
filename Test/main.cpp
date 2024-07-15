
/*

#include <WhaleLanguage/Lexer/Lexer.h>

#include <boost/make_shared.hpp>
#include <boost/json/src.hpp>
#include <boost/format.hpp>
using namespace Whale;

void LexerOut(const boost::json::value &a, const std::string &fileName);

void LexerIn(std::list<boost::shared_ptr<Token>> &list, const std::string &fileName);

void LexerToJson(std::list<boost::shared_ptr<Token>> &list, boost::json::object &a);

int main()
{
	
	std::list<boost::shared_ptr<Token>> list;
	LexerIn(list, "./Data/code.cs");
	
	boost::json::object a;
	LexerToJson(list, a);
	
	LexerOut(a, "lexer.json");
	
	//system("pause");
	
	return 0;
}

void LexerToJson(std::list<boost::shared_ptr<Token>> &list, boost::json::object &a)
{
	size_t count = 0;
	for (auto& item: list)
	{
		boost::json::object obj;
		obj["type"] = item->GetTypeName();
		obj["str"] = item->str;
		obj["pos"] = (boost::format("(%d, %d)") % item->pos.line % item->pos.ch).str();
		a[std::to_string(++count)] = obj;
	}
}

void LexerIn(std::list<boost::shared_ptr<Token>> &list, const std::string &fileName)
{
	boost::filesystem::ifstream fileStream(fileName);
	
	boost::shared_ptr<Lexer> lexer = boost::make_shared<Lexer>(fileStream);
	
	
	list = lexer->NextTokens();
	fileStream.close();
}

void LexerOut(const boost::json::value &a, const std::string &fileName)
{
	boost::filesystem::ofstream fileStream(fileName);
	fileStream << boost::json::serialize(a);
	fileStream.close();
}

/*/

#include <Whale/Win32/FMessageBox.hpp>
#include <Whale/Win32/WWindow.hpp>

#include <memory>
#include <boost/json.hpp>
#include <boost/filesystem/fstream.hpp>
#include "Whale/Core/FDebug.hpp"
#include "Whale/Core/WProgram.hpp"
#include "Whale/Render/WRenderer.hpp"
#include "Whale/Render/WShader.hpp"
#include "Whale/Render/WStaticMesh.hpp"

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
	
	uint64 OnChar(const TChar &input) override
	{
		return WWindow::OnChar(input);
	}
	
	uint64 OnString(const FTString<TChar> &input) override
	{
		return WWindow::OnString(input);
	}
	
	uint64 OnKeyDown(const EventKeyArgs &args) override
	{
		return WWindow::OnKeyDown(args);
	}
	
	void OnTick(float deltaTIme) override;
	
	uint64 OnDestroy() override
	{
		Win32::FCore::Exit();
		return WWindow::OnDestroy();
	}

public:
	
	class Program &program;
	
	[[nodiscard]]
	const std::shared_ptr<WWindowRenderTarget> &GetPRenderTarget() const
	{
		return pRenderTarget;
	}

private:
	
	std::shared_ptr<WWindowRenderTarget> pRenderTarget;
	
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
	
	void InitDirectX()
	{
		pRenderTarget = std::make_shared<WWindowRenderTargetDirectX>();
		pRenderTarget->Create(*this);
	}

protected:
	
	void OnTick(float deltaTIme) override
	{
		Win32::WWindow::OnTick(deltaTIme);
	}

public:
	
	class Program &program;
	
	[[nodiscard]]
	const std::shared_ptr<WWindowRenderTarget> &GetPRenderTarget() const
	{
		return pRenderTarget;
	}

private:
	
	std::shared_ptr<WWindowRenderTarget> pRenderTarget;
	
};

class Program : public WProgram
{
public:
	
	void InitData()
	{
		pWindowClass = std::make_unique<Win32::WWindow::WWindowClass>(
			Win32::FCore::GetInstance(), WHALE_WIDE("WhaleTestWindowClass")
		);
		if (!pWindowClass->Register())
		{
			FDebug::Fatal((
							  L"Register Window Class Failed!\r\nError: " +
							  Win32::FCore::MessageToStringW(Win32::FCore::GetLastError())).c_str());
			throw;
		}
		
		pWindow = std::make_unique<MyWindow>(*this);
		pWindow->Create(*pWindowClass, WHALE_WIDE("Whale Test"));
		if (pWindow->GetHWindow().handle == nullptr)
		{
			FDebug::Fatal((
							  L"Create Window Failed!\r\nError: " +
							  Win32::FCore::MessageToStringW(Win32::FCore::GetLastError())).c_str());
			throw;
		}
		pWindow->ShowAndUpdate();
		
		pWindow2 = std::make_unique<MyWindow2>(*this);
		pWindow2->Create(*pWindowClass, WHALE_WIDE("Whale Test 2"));
		if (pWindow2->GetHWindow().handle == nullptr)
		{
			FDebug::Fatal((
							  L"Create Window Failed!\r\nError: " +
							  Win32::FCore::MessageToStringW(Win32::FCore::GetLastError())).c_str());
			throw;
		}
		pWindow2->ShowAndUpdate();
		
		boost::filesystem::ifstream dataFile{"./Data/data.json"};
		if (!dataFile.is_open())
		{
			FDebug::Fatal(L"cannot to open \"./Data/data.json\"");
			throw;
		}
		boost::json::object dataObject;
		{
			boost::json::value dataValue = boost::json::parse(dataFile);
			if (!dataValue.is_object())
			{
				FDebug::Fatal(L"data isn't a [JSON object]");
				throw;
			}
			dataObject = dataValue.as_object();
		}
		this->data.toEncoding = dataObject["toEncoding"].as_string();
		this->data.fromEncoding = dataObject["fromEncoding"].as_string();
		this->data.windowData.name = dataObject["windowData"].as_object()["name"].as_string();
		this->data.windowData.name = WLocale::Between(
			this->data.windowData.name, this->data.toEncoding, this->data.fromEncoding
		);
		this->data.shader = dataObject["shader"].as_string();
		this->pWindow->SetName(this->data.windowData.name);
		this->pWindow2->SetName(this->data.windowData.name + " II");
	}
	
	void InitDirectX()
	{
		pRender.reset(WRenderer::NewRenderer(Whale::WRenderer::DirectX));
		pShader = std::make_unique<WShaderDirectX12>();
		pMesh = std::make_unique<WStaticMeshDirectX12>();
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
		std::string toEncoding;
		std::string fromEncoding;
		struct WindowData
		{
			std::string name;
		} windowData;
		std::string shader;
	} data;
	
	std::unique_ptr<MyWindow> pWindow;
	
	std::unique_ptr<MyWindow2> pWindow2;
	
	std::unique_ptr<Win32::WWindow::WWindowClass> pWindowClass;
	
	std::unique_ptr<WRenderer> pRender;
	
	std::shared_ptr<WShader> pShader;
	
	std::shared_ptr<WStaticMesh> pMesh;

public:
	
	[[nodiscard]]
	const struct Data &GetData() const
	{
		return data;
	}
	
	[[nodiscard]]
	const std::unique_ptr<MyWindow> &GetPWindow() const
	{
		return pWindow;
	}
	
	[[nodiscard]]
	const std::unique_ptr<Win32::WWindow::WWindowClass> &GetPWindowClass() const
	{
		return pWindowClass;
	}
	
	[[nodiscard]]
	const std::unique_ptr<WRenderer> &GetPRender() const
	{
		return pRender;
	}
	
	[[nodiscard]]
	const std::shared_ptr<WShader> &GetPShader() const
	{
		return pShader;
	}
	
};

void MyWindow::InitDirectX()
{
	pRenderTarget = std::make_shared<WWindowRenderTargetDirectX>();
	pRenderTarget->Create(*this);
}

void MyWindow::OnTick(float deltaTIme)
{
	WWindow::OnTick(deltaTIme);
}


int main()
{
	FDebug::LogToFile(".\\logs\\%Y%m%d.log");
	Program program;
	return program.Run();
}

#include <Whale/Win32/FWinMain.hpp>
//*/

