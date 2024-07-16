//
// Created by admin on 2024/6/14.
//

#pragma once

#include <Windows.h>
#include <tchar.h>


int main();

int _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
#if defined(_DEBUG) || defined(DEBUG)
	// 当为DEBUG模式时，启用内存泄漏检测
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	int result = main();
#if defined(_DEBUG) || defined(DEBUG)
	_CrtDumpMemoryLeaks();
#endif
	return result;
}
