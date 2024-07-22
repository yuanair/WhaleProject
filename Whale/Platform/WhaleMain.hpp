//
// Created by admin on 2024/7/22.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"

int WhaleMain();

#if WHALE_TARGET == WHALE_TARGET_WINDOWS
	
	#include "./WhaleMain.hpp"

#else

int main()
{
	return ::WhaleMain();
}

#endif
