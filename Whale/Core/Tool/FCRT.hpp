//
// Created by admin on 2024/7/16.
//

#pragma once


#if defined(_DEBUG) || defined(DEBUG)

#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>

#define WHALE_DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type

#else

#define WHALE_DBG_NEW new

#endif
