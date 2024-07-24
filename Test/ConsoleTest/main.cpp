
#include "CommandManager.hpp"
#include "Whale/Language/Lexer.hpp"
#include "Whale/Core/Container/StringStream.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <format>

Json::JsonT value(Json::ETypeObject);

using MyCommandManager = CommandManager<CharT>;

void Show(MyCommandManager &commandManager)
{
	if (FLocale::IsNewLine(commandManager.in.GetPeek()))
	{
		commandManager.out.WriteLine(value.ToString());
	}
	else
	{
		StringT arg1;
		commandManager.in.Read(arg1);
		if (value.Has(arg1))
		{
			commandManager.out.WriteLine(value.KeyToString(arg1));
		}
		else
		{
			commandManager.errors.Append(WHALE_TEXT("Unknown key"));
		}
	}
}

void Set(MyCommandManager &commandManager)
{
	StringT arg1, arg2;
	commandManager.in.Read(arg1);
	commandManager.in.Read(arg2);
	value[arg1] = arg2;
	commandManager.out.WriteLine(value.KeyToString(arg1));
}

void Remove(MyCommandManager &commandManager)
{
	StringT arg1;
	commandManager.in.Read(arg1);
	if (!value.Remove(arg1)) commandManager.errors.Append(WHALE_TEXT("Remove failed!"));
}

void Cls(MyCommandManager &commandManager)
{
	commandManager.out.Write(WHALE_TEXT("\x1B[2J\x1B[H"));
}

void Lex(MyCommandManager &commandManager)
{
	StringT arg1;
	commandManager.in.ReadTo(arg1, [](int32 elem) -> Bool { return -1 == elem; });
	Container::StringStreamReaderT ss(arg1);
	TWLexer<CharT> lexer{ss};
	while (!lexer.IsEOF())
	{
		auto pToken = lexer.Read();
		if (pToken) commandManager.out.WriteLine(pToken->GetTypeString() + WHALE_TEXT(": ") + pToken->ToString());
	}
	for (auto &error: lexer.GetErrors())
	{
		commandManager.out.WriteLine(
			std::format(
				WHALE_TEXT("Error: ({}, {}): {}: {}"), error.pos.line, error.pos.column, (int32) error.error,
				error.message.CStr()
			).c_str());
	}
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
	
	ConsoleT console;
	
	MyCommandManager commandManager{console.in, console.out};
	commandManager.commands.insert(
		{
			{WHALE_TEXT("show"),       Show},
			{WHALE_TEXT("set"),        Set},
			{WHALE_TEXT("remove"),     Remove},
			{WHALE_TEXT("cls"),        Cls},
			{WHALE_TEXT("listColors"), ListColors},
			{WHALE_TEXT("lex"),        Lex}
		}
	);
	
	while (true)
	{
		StringT command, arg1;
		console.Write(WHALE_TEXT("> "));
		console.Read(command);
		if (command == WHALE_TEXT("exit")) break;
		
		commandManager.Run(command);
		for (auto &item: commandManager.errors)
		{
			console.WriteLine(item);
		}
		
		commandManager.errors.Clear();
		console.ClearInBuffer();
		console.ClearError();
	}
	console.WriteLine(WHALE_TEXT("Thanks for using"));
	
	FDebug::LogClose();
	value = nullptr;
	
	return 0;
}

#include "Whale/Platform/WhaleMain.hpp"
//*/

