//
// Created by admin on 2024/7/15.
//

#include "FReflect.hpp"

namespace Whale
{
	
	std::vector<const WClass *> FReflect::classes{};
	
	std::vector<const WEnum *> FReflect::enums{};
	
	std::vector<const WUnion *> FReflect::unions{};
	
} // Whale