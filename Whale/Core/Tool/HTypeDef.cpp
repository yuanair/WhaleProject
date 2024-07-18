//
// Created by admin on 2024/6/16.
//

#include "HTypeDef.hpp"

#if defined(DEBUG) || defined(_DEBUG)

#include <cassert>

#else

#include "Whale/Core/Debug/FDebug.hpp"
#include "Whale/Core/Object/WProgram.hpp"

#endif

namespace Whale
{
	WHALE_API void FatalMessage(const WChar *message, const WChar *file, uint64 line, const WChar *function)
	{
#if defined(DEBUG) || defined(_DEBUG)
		_wassert(message, file, (uint32) line);
#else
		FDebug::LogFatal(WProgram::GetAppNameW(), message);
#endif
	}
} // Whale