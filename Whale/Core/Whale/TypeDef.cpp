//
// Created by admin on 2024/6/16.
//

#include "TypeDef.hpp"

#include <Windows.h>

namespace Whale
{
	void Assert(const CharA *message, const CharA *file, uint64 line, const CharA *function)
	{
		int result = ::MessageBoxA(
			nullptr, "Press Retry to debug the application", WHALE_STRING(WHALE_ASSERT),
			MB_ABORTRETRYIGNORE | MB_ICONSTOP | MB_DEFBUTTON2
		);
		if (result == IDRETRY) throw;
		if (result == IDABORT) exit(3);
		if (result == IDIGNORE) return;
		throw;
	}
	
	void Assert(const CharW *message, const CharW *file, uint64 line, const CharW *function)
	{
		int result = ::MessageBoxW(
			nullptr, WTEXT("Press Retry to debug the application"), WHALE_WIDE(WHALE_STRING(WHALE_ASSERT)),
			MB_ABORTRETRYIGNORE | MB_ICONSTOP | MB_DEFBUTTON2
		);
		if (result == IDRETRY) throw;
		if (result == IDABORT) exit(3);
		if (result == IDIGNORE) return;
		throw;
	}
} // Whale