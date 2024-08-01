//
// Created by admin on 2024/7/22.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/Memory.hpp>
#include <Whale/Stream.hpp>
#include "Token.hpp"

namespace Whale
{
	
	///
	/// 词法分析器
	template<class ElemT>
	class WHALE_API TILexer : public TIStreamReader<TFUniquePtr<TWToken<ElemT>>>
	{
	public:
		
		TFUniquePtr<TWToken<ElemT>> Peek() noexcept override = 0;
		
		TFUniquePtr<TWToken<ElemT>> Read() noexcept override = 0;
		
	};
	
} // Whale
