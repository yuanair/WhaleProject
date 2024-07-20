

#include "CommandManager.hpp"


Json::JsonT value(Json::ETypeObject);

using MyCommandManager = CommandManager<CharT>;

void Show(MyCommandManager &commandManager)
{
	if (FLocale::IsNewLine(commandManager.in.Peek()))
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

int WhaleMain()
{
	//FDebug::LogToFile(".\\logs\\%Y%m%d.log");
	
	MyCommandManager commandManager{ConsoleT::in, ConsoleT::out};
	commandManager.commands.insert(
		{
			{WHALE_TEXT("show"),   Show},
			{WHALE_TEXT("set"),    Set},
			{WHALE_TEXT("remove"), Remove}
		}
	);
	
	while (true)
	{
		StringT command, arg1;
		ConsoleT::Write(WHALE_TEXT("> "));
		ConsoleT::Read(command);
		if (command == WHALE_TEXT("exit")) break;
		
		commandManager.Run(command);
		for (auto &item: commandManager.errors)
		{
			ConsoleT::WriteLine(item);
		}
		
		commandManager.errors.Clear();
		ConsoleT::ClearInBuffer();
		
	}
	ConsoleT::WriteLine(WHALE_TEXT("Thanks for using"));
	
	//FDebug::LogClose();
	value = nullptr;
	
	return 0;
}

#include "Whale/Platform/Win32/WinMain.hpp"
//*/

