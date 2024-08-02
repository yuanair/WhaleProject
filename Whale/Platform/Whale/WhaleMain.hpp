//
// Created by admin on 2024/7/22.
//

#pragma once

#include <Whale/TypeDef.hpp>

int WhaleMain();

#ifdef WHALE_TARGET_WINDOWS

#include <Windows.h>
#include <tchar.h>


int WINAPI _tWinMain(::HINSTANCE, ::HINSTANCE, ::LPTSTR, int)
{
	::_CrtMemState s1, s2, s3;
#if defined(_DEBUG) || defined(DEBUG)
	// 当为DEBUG模式时，启用内存泄漏检测
	::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	::_CrtMemCheckpoint(&s1);

#endif
	int result = ::WhaleMain();
#if defined(_DEBUG) || defined(DEBUG)
	::_CrtMemCheckpoint(&s2);
	if (::_CrtMemDifference(&s3, &s1, &s2))
	{
		::_CrtMemDumpStatistics(&s3);
	}
	::_CrtDumpMemoryLeaks();
#endif
	return result;
}

int main()
{
	::_CrtMemState s1, s2, s3;
#if defined(_DEBUG) || defined(DEBUG)
	// 当为DEBUG模式时，启用内存泄漏检测
	::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	::_CrtMemCheckpoint(&s1);

#endif
	int result = ::WhaleMain();
#if defined(_DEBUG) || defined(DEBUG)
	::_CrtMemCheckpoint(&s2);
	if (::_CrtMemDifference(&s3, &s1, &s2))
	{
		::_CrtMemDumpStatistics(&s3);
	}
	::_CrtDumpMemoryLeaks();
#endif
	return result;
}

#else

int main()
{
	return ::WhaleMain();
}

#endif
