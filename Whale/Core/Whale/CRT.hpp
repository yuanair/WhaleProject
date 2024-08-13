//
// Created by admin on 2024/7/16.
//

#pragma once


#if defined(_DEBUG) || defined(DEBUG)

#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>

#define WHALE_NEW_NORMAL new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define WHALE_NEW_CLIENT new ( _CLIENT_BLOCK , __FILE__ , __LINE__ )
#define WHALE_NEW_IGNORE new ( _IGNORE_BLOCK , __FILE__ , __LINE__ )
#define WHALE_NEW_S(sourceLocation) new ( _NORMAL_BLOCK , (sourceLocation).FileName() , (sourceLocation).Line() )

#else

#define WHALE_NEW_NORMAL new
#define WHALE_NEW_CLIENT new
#define WHALE_NEW_IGNORE new
#define WHALE_NEW_S(sourceLocation) new

#endif
