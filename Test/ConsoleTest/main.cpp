#include "Whale/Core/FDebug.hpp"
#include "Whale/Core/FConsole.hpp"
#include "Whale/Language/Json/TFValue.hpp"

using namespace Whale;

int WhaleMain()
{
	FDebug::LogToFile(".\\logs\\%Y%m%d.log");
	
	Language::Json::JsonT value;
	
	while (true)
	{
		StringT input;
		FConsole::Write(WHALE_TEXT("> "));
		FConsole::ReadLine(input);
		
		if (input == WHALE_TEXT("exit")) break;
		else if (input == WHALE_TEXT("debug"))
		{
		
		}
		else value[input] = nullptr;
		
	}
	
	FDebug::LogClose();
	
	return 0;
}

#include "Whale/Render/Win32/FWinMain.hpp"
//*/

