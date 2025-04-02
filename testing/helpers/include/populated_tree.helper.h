#pragma once
#include "general_tree.h"
#include <vector>

class populated_tree
{
public:		
	static inline const std::vector<int> preorder_vector = { 1, 30, 33, 32, 31, 311, 20, 203, 202, 201, 10, 102, 101 };
	static inline const std::vector<int> postorder_vector = { 33, 32, 311, 31, 30, 203, 202, 201, 20, 102, 101, 10, 1 };	
	static general_tree<int> create();
};