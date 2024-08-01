//
// Created by admin on 2024/7/20.
//

#pragma once

#include "Whale/Core/Whale/FDebug.hpp"
#include "Whale/Core/Whale/TFConsole.hpp"
#include "Whale/Language/Json/TFValue.hpp"
#include "Whale/Language/Whale/Lexer.hpp"
#include "Whale/Core/Container/StringStream.hpp"

#include <map>
#include <format>

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
	
	TFUniquePtr<TWToken<ElemT>> NextToken();

public:
	
	std::map<String, TFFunction<void, CommandManager &>> commands;
	
	Container::TFArray<String> errors;
	
	TFUniquePtr<TWLexer<ElemT>> pLexer;
	
	FileStream &in;
	
	FileStream &out;
	
	Bool isExit = false;
	
};

template<class ElemT>
TFUniquePtr<TWToken<ElemT>> CommandManager<ElemT>::NextToken()
{
	TFUniquePtr<TWToken<ElemT>> pToken = pLexer->Read();
	out.WriteLine(std::format(WHALE_TEXT("{}: {}"), (int32) pToken->m_type, pToken->m_str.CStr()).c_str());
	return pToken;
}

template<class ElemT>
void CommandManager<ElemT>::Run(const String &command)
{
	Container::StringStreamReaderT ss(command);
	pLexer = MakeUnique<TWLexer<ElemT>>(ss);
	
	auto pToken = NextToken();
	
	if (pToken->m_type == ETokenTypeIdentifier)
	{
		auto iter = this->commands.find(pToken->m_str);
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
	else
	{
		errors.Append(WHALE_TEXT("Unknown command!"));
	}
	
	
	for (auto &error: pLexer->GetErrors())
	{
		errors.Append(
			std::format(
				WHALE_TEXT("Error: ({}, {}): {}: {}"), error.pos.line, error.pos.column, (int32) error.error,
				error.message.CStr()
			).c_str());
	}
	
}

template<class ElemT>
CommandManager<ElemT>::CommandManager(FileStream &in, FileStream &out) : in(in), out(out) {}
