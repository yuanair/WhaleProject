//
// Created by admin on 2024/6/16.
//

#include "FTypeDef.hpp"

#if defined(DEBUG) || defined(_DEBUG)
#include <cassert>
#else

#include "FDebug.h"

#endif

namespace Whale
{
	WHALE_API void FatalMessage(const WChar *message, const WChar *file, uint64 line, const WChar *function)
	{
#if defined(DEBUG) || defined(_DEBUG)
		_wassert(message, file, line);
#else
		FDebug::Fatal(message);
#endif
	}
} // Whale