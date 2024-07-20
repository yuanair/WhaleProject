//
// Created by admin on 2024/7/20.
//

#pragma once

#include "Whale/Core/FDebug.hpp"
#include "Whale/Core/TFConsole.hpp"
#include "Whale/Language/Json/TFValue.hpp"

#include <map>

using namespace Whale;

template<class ElemT>
class CommandManager
{
public:
	
	using String = Container::TFString<ElemT>;
	
	using FileStream = IO::FFileStream<ElemT>;

public:
	
	explicit CommandManager(FileStream &in, FileStream &out);

public:
	
	void Run(const String &command);

public:
	
	std::map<String, std::function<void(CommandManager &)>> commands;
	
	Container::TFArray<String> errors;
	
	FileStream &in;
	
	FileStream &out;
	
};

template<class ElemT>
void CommandManager<ElemT>::Run(const String &command)
{
	auto iter = this->commands.find(command);
	if (iter == this->commands.end())
	{
		errors.Append(WHALE_TEXT("Unknown command!"));
		return;
	}
	if (!iter->second)
	{
		errors.Append(WHALE_TEXT("Command is not link!"));
		return;
	}
	iter->second(*this);
}

template<class ElemT>
CommandManager<ElemT>::CommandManager(FileStream &in, FileStream &out) : in(in), out(out) {}
