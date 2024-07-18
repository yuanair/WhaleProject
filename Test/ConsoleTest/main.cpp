#include "Whale/Core/Debug/FDebug.hpp"
#include "Whale/Language/Json/TFValue.hpp"

#include <iostream>
#include <string>

using namespace Whale;

int main()
{
	FDebug::LogToFile(".\\logs\\%Y%m%d.log");
	
	Language::Json::JsonA value;
	std::string input;
	
	while (true)
	{
		std::cout << "> ";
		std::getline(std::cin, input);
		
		value[input.c_str()] = nullptr;
		
	}
	
	FDebug::LogClose();
	
	return 0;
}

#include "Whale/Render/Win32/FWinMain.hpp"
//*/

