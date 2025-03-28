#include <gtest/gtest.h>
#include <vector>
#include "general-tree.h"
#include "populated_tree.helper.h"

TEST(class_const_iterator, forEachOperator_ShouldUsePreorderByDefault)
{
	std::vector<int> elements;
	auto order = general_tree<int>::iteration_type::preorder;	

	for (int e : std::as_const(populated_tree::tree))
		elements.push_back(e);

	EXPECT_EQ(elements, populated_tree::preorder_vector);
}