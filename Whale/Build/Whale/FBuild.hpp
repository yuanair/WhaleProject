//
// Created by admin on 2024/8/13.
//

#pragma once

#include <Whale/TypeDef.hpp>
#include <Whale/Container/TFString.hpp>

namespace Whale
{
	
	/// 参数
	struct WHALE_API BuildArg
	{
		FString name;
		FString buildDir;
		FString outFile;
	};
	
	/// 构建类
	class WHALE_API FBuild
	{
	public:
		
		static void Build(const BuildArg &arg);
		
	};
	
} // Whale
