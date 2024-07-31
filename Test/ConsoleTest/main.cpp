
#include "CommandManager.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

Json::JsonT value(Json::ETypeObject);

using MyCommandManager = CommandManager<CharT>;

void Show(MyCommandManager &commandManager)
{
	auto pToken = commandManager.NextToken();
	if (pToken->m_type == ETokenTypeIdentifier)
	{
		if (value.Has(pToken->m_str))
		{
			commandManager.out.WriteLine(value.KeyToString(pToken->m_str));
		}
		else
		{
			commandManager.errors.Append(WHALE_TEXT("Unknown key\"") + pToken->m_str + WHALE_TEXT("\""));
			return;
		}
	}
	else if (pToken->m_type == ETokenTypeEOF)
	{
		commandManager.out.WriteLine(value.ToString());
	}
	else
	{
		commandManager.errors.Append(WHALE_TEXT("error arg!"));
		return;
	}
}

void Set(MyCommandManager &commandManager)
{
	StringT arg;
	auto    pToken = commandManager.NextToken();
	if (pToken->m_type == ETokenTypeIdentifier)
	{
		arg = pToken->m_str;
	}
	else
	{
		commandManager.errors.Append(WHALE_TEXT("error arg!"));
		return;
	}
	pToken         = commandManager.NextToken();
	if (pToken->m_type == ETokenTypeString)
	{
		value[arg] = pToken->m_str;
	}
	else
	{
		commandManager.errors.Append(WHALE_TEXT("error value!"));
		return;
	}
}

void Remove(MyCommandManager &commandManager)
{
	auto pToken = commandManager.NextToken();
	if (pToken->m_type == ETokenTypeIdentifier)
	{
		if (value.Has(pToken->m_str))
		{
			value.Remove(pToken->m_str);
		}
		else
		{
			commandManager.errors.Append(WHALE_TEXT("Unknown key\"") + pToken->m_str + WHALE_TEXT("\""));
			return;
		}
	}
	else
	{
		commandManager.errors.Append(WHALE_TEXT("error arg!"));
		return;
	}
}

void Cls(MyCommandManager &commandManager)
{
	commandManager.out.Write(WHALE_TEXT("\x1B[2J\x1B[H"));
}

void ListColors(MyCommandManager &commandManager)
{
	for (SizeT index = 0; index < 256; index++)
	{
		commandManager.out.Write(std::format(WHALE_TEXT("\x1B[38;5;{0}m{0} "), index).c_str());
		if ((index + 15) % 6 == 0) commandManager.out.WriteLine();
	}
	commandManager.out.WriteLine();
}

int WhaleMain()
{
	FDebug::LogToFile(".\\logs\\%Y%m%d.log");
	
	ConsoleT        console;
	IO::FileStreamT &in = console.in;
	IO::FileStreamT out{WHALE_TEXT("./test.txt"), WHALE_TEXT("w")};
	
	MyCommandManager commandManager{in, out};
	
	commandManager.commands.insert(
		{
			{WHALE_TEXT("exit"),       [](MyCommandManager &commandManager) -> void { commandManager.isExit = true; }},
			{WHALE_TEXT("show"),       Show},
			{WHALE_TEXT("set"),        Set},
			{WHALE_TEXT("remove"),     Remove},
			{WHALE_TEXT("cls"),        Cls},
			{WHALE_TEXT("listColors"), ListColors}
		}
	);
	
	while (!commandManager.isExit)
	{
		StringT command{};
		out.Write(WHALE_TEXT("> "));
		in.ReadLine(command);
		
		commandManager.Run(command);
		for (auto &item: commandManager.errors)
		{
			out.WriteLine(item);
		}
		
		commandManager.errors.Clear();
		// console.ClearError();
		console.ClearInBuffer();
	}
	out.WriteLine(WHALE_TEXT("Thanks for using"));
	
	FDebug::LogClose();
	value = nullptr;
	
	return 0;
}

#include "Whale/Platform/WhaleMain.hpp"
//*/

