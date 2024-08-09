

#include "CommandManager.hpp"
#include "Whale/Container/TFRange.hpp"
#include "Whale/Container/TFDynamicArray.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <random>

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

ConsoleT &GetConsole()
{
	static ConsoleT console;
	return console;
}

template<class ElemT>
class DebugCLass
{
public:
	
	DebugCLass()
		: bIsMoved(false), m_elem()
	{
		static uint64 count = 0;
		GetConsole().WriteLine(std::format(WTEXT("{}::{}"), WHALE_WIDE("default"), ++count).c_str());
	}
	
	DebugCLass(ElemT elem)
		: bIsMoved(false), m_elem(Whale::Move(elem))
	{
		static uint64 count = 0;
		GetConsole().WriteLine(std::format(WTEXT("{}::{}"), WHALE_WIDE("elem"), ++count).c_str());
	}
	
	DebugCLass(const DebugCLass &a)
		: bIsMoved(false), m_elem(a.m_elem)
	{
		static uint64 count = 0;
		GetConsole().WriteLine(std::format(WTEXT("{}::{}"), WHALE_WIDE("copy"), ++count).c_str());
	}
	
	DebugCLass(DebugCLass &&a)
		: bIsMoved(false), m_elem(a.m_elem)
	{
		static uint64 count = 0;
		if (a.bIsMoved) throw;
		a.bIsMoved = true;
		a.m_elem   = 0xddccbb;
		GetConsole().WriteLine(std::format(WTEXT("{}::{}"), WHALE_WIDE("move"), ++count).c_str());
	}
	
	~DebugCLass()
	{
		static uint64 count = 0;
		this->m_elem = 0xddccbb;
		GetConsole().WriteLine(std::format(WTEXT("{}::{}"), WHALE_WIDE("destroy"), ++count).c_str());
	}

public:
	
	DebugCLass &operator=(DebugCLass a)
	{
		static uint64 count = 0;
		this->bIsMoved = false;
		this->m_elem   = a.m_elem;
		GetConsole().WriteLine(std::format(WTEXT("{}::{}"), WHALE_WIDE("assign"), ++count).c_str());
		return *this;
	}

public:
	
	operator ElemT() const { return m_elem; }
	
	operator ElemT() { return m_elem; }

private:
	
	Bool bIsMoved;
	
	ElemT m_elem;
	
};

#include <memory>
#include <string>

int WhaleMain()
{
	
	IO::FileStreamT &in  = GetConsole().in;
	IO::FileStreamT &out = GetConsole().out;
	
	MyCommandManager commandManager{in, out};
	
	using ElemType = DebugCLass<std::wstring>;
	
	Container::TFDynamicArray<ElemType> arr;
	std::vector<ElemType>               vec;
	std::random_device                  rd;
	std::mt19937                        gen(rd());
	int                                 y = 5, oldC = 0, count = 0;
	
	while (y--)
	{
		arr += std::to_wstring(y);
		//vec.emplace_back(std::to_wstring(y));
	}
	
	arr.AdjustLength(6);

//	while (!arr.IsEmpty())
//	{
//		arr.PopBack();
//		GetConsole().WriteLine(
//			std::format(
//				WTEXT("x_{{{0}}} = {1}"),
//				++count,
//				arr.GetLength()
//			).c_str());
//	}
	
	for (auto iter = vec.rbegin(); iter < vec.rend(); iter += 1)
	{
		GetConsole().WriteLine(std::format(WTEXT("{:}"), iter->operator std::wstring()).c_str());
		// GetConsole().WriteLine(std::format(WTEXT("{:}"), (UIntPointer) ((iter - arr.rbegin()))).c_str());
	}
	
	for (auto iter = arr.rbegin(); iter < arr.rend(); iter += 1)
	{
		GetConsole().WriteLine(std::format(WTEXT("{:}"), iter->operator std::wstring()).c_str());
		// GetConsole().WriteLine(std::format(WTEXT("{:}"), (UIntPointer) ((iter - arr.rbegin()))).c_str());
	}
	
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
		// GetConsole().ClearError();
		GetConsole().ClearInBuffer();
	}
	out.WriteLine(WHALE_TEXT("Thanks for using"));
	
	value = nullptr;
	
	return 0;
}

#include "Hello.h"

/*
extrn MessageBoxA: proc

.data
text db 'Hello World', 0
caption db 'Selph First x64 Application', 0

.code
HelloMain proc
sub rsp,28h ; 函数调用前需要预留影子空间，对齐rsp
xor r9d,r9d
lea r8, caption
lea rdx, text
xor rcx,rcx
call MessageBoxA ; 函数调用使用fastcall
add rsp,28h
ret
HelloMain ENDP
END
 */

#include <Whale/WhaleMain.hpp>
