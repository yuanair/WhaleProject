//
// Created by admin on 2024/6/16.
//

#include "TypeDef.hpp"

#if defined(DEBUG) || defined(_DEBUG)

#include <cassert>

#else

#include "Whale/Core/FDebug.hpp"
#include "WProgram.hpp"

#endif

namespace Whale
{
	WHALE_API void FatalMessage(const CharW *message, const CharW *file, uint64 line, const CharW *function)
	{
#if defined(DEBUG) || defined(_DEBUG)
		_wassert(message, file, (uint32) line);
#else
		FDebug::LogFatal(WProgram::GetAppNameW(), message);
#endif
	}
} // Whale