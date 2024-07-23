//
// Created by admin on 2024/7/22.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"
#include "Whale/Core/Memory.hpp"
#include "Token.hpp"

namespace Whale
{
	
	///
	/// 词法分析器
	template<class ElemT>
	class WHALE_API TILexer
	{
	public:
		
		virtual TFUniquePtr<TWToken<ElemT>> Get() = 0;
		
	};
	
} // Whale
