//
// Created by admin on 2024/7/19.
//

#include "FConsole.hpp"

namespace Whale
{
	void FConsole::Write(const StringA &str)
	{
		outA.Write(str);
	}
	
	void FConsole::Write(const StringW &str)
	{
		outW.Write(str);
	}
	
	void FConsole::WriteLine(const StringA &str)
	{
		outA.WriteLine(str);
	}
	
	void FConsole::WriteLine(const StringW &str)
	{
		outW.WriteLine(str);
	}
	
	CharA FConsole::ReadA()
	{
		return inA.Get();
	}
	
	CharW FConsole::ReadW()
	{
		return inW.Get();
	}
	
	void FConsole::ReadLine(StringA &str)
	{
		inA.ReadTo(str, [](CharA elem) -> Bool { return elem == '\n' || elem == '\r'; });
	}
	
	void FConsole::ReadLine(StringW &str)
	{
		inW.ReadTo(str, [](CharA elem) -> Bool { return elem == '\n' || elem == '\r'; });
	}
	
	IO::FileStreamA FConsole::outA{stdout, false};
	
	IO::FileStreamW FConsole::outW{stdout, false};
	
	IO::FileStreamA FConsole::inA{stdin, false};
	
	IO::FileStreamW FConsole::inW{stdin, false};
	
	IO::FileStreamA FConsole::errA{stderr, false};
	
	IO::FileStreamW FConsole::errW{stderr, false};
	
	
} // Whale