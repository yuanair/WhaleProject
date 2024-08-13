//
// Created by admin on 2024/8/13.
//

#include <Whale/TypeDef.hpp>
#include <Whale/FBuild.hpp>

using namespace Whale;

int32 WhaleMain()
{
	
	FBuild::Build(
		{.name=WTEXT(""), .buildDir=WTEXT("D:/WhaleProject"), .outFile=WTEXT("D:/WhaleProject/Whale/Whale.txt")}
	);
	
	return 0;
}

#include <Whale/WhaleMain.hpp>
