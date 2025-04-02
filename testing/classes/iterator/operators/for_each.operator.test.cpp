#include <gtest/gtest.h>
#include <vector>
#include "general-tree.h"
#include "populated_tree.helper.h"

TEST(class_iterator, forEachOperator_preorderIsTheIterationType)
{	
	general_tree<int> test_tree = populated_tree::create();

	std::vector<int> elements;
	auto order = general_tree<int>::iteration_type::preorder;

	for (int e : test_tree)
		elements.push_back(e);

	EXPECT_EQ(elements, populated_tree::preorder_vector);
}
