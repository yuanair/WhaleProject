//
// Created by admin on 2024/7/23.
//

#pragma once

#include "../Utility.hpp"
#include "../CRT.hpp"
#include "InitList.hpp"

namespace Whale
{
	
	///
	/// 二叉树
	template<class ElemT>
	class TFTree
	{
	public:
		
		TFTree() noexcept: value(), left(nullptr), right(nullptr) {}
		
		explicit TFTree(ElemT elem) noexcept: value(Whale::Move(elem)), left(nullptr), right(nullptr) {}
		
		TFTree(const TFTree &other) noexcept
			: value(other.value), left(other.HasLeft() ? WHALE_NEW_CLIENT TFTree(*other.left) : nullptr),
			  right(other.HasRight() ? WHALE_NEW_CLIENT TFTree(*other.right) : nullptr) {}
		
		TFTree(TFTree &&other) noexcept: TFTree()
		{
			Swap(other);
		}
		
		~TFTree() noexcept { Reset(); }
	
	public:
		
		void Swap(TFTree &other) noexcept
		{
			if (this == &other) return;
			Whale::Swap(left, other.left);
			Whale::Swap(right, other.right);
			using Whale::Swap;
			Swap(value, other.value);
		}
		
		void Reset(TFTree *leftTree = nullptr, TFTree *rightTree = nullptr) noexcept
		{
			if (left != nullptr) delete left;
			if (right != nullptr) delete right;
			left  = leftTree;
			right = rightTree;
		}
		
		TFTree *ResetLeft(TFTree *tree = nullptr) noexcept
		{
			if (left != nullptr) delete left;
			left = tree;
			return tree;
		}
		
		TFTree *ResetRight(TFTree *tree = nullptr) noexcept
		{
			if (right != nullptr) delete right;
			right = tree;
			return tree;
		}
		
		TFTree *ReleaseLeft() noexcept
		{
			TFTree *temp = left;
			left = nullptr;
			return temp;
		}
		
		TFTree *ReleaseRight() noexcept
		{
			TFTree *temp = right;
			right = nullptr;
			return temp;
		}
	
	public:
		
		[[nodiscard]] Bool HasLeft() const noexcept { return left != nullptr; }
		
		[[nodiscard]] Bool HasRight() const noexcept { return right != nullptr; }
		
		TFTree *GetLeft() const noexcept { return left; }
		
		TFTree *GetRight() const noexcept { return right; }
	
	public:
		
		ElemT value;
	
	private:
		
		TFTree *left;
		
		TFTree *right;
		
	};
	
} // Whale
