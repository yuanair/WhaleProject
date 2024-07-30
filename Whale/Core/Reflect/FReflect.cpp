//
// Created by admin on 2024/7/15.
//

#include "FReflect.hpp"

namespace Whale::Reflect
{
	
	Container::TFArray<WClass> FReflect::classes{};
	
	Container::TFArray<WEnum> FReflect::enums{};
	
	Container::TFArray<WUnion> FReflect::unions{};
	
} // Whale