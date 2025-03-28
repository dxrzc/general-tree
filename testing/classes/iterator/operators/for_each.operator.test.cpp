#include <gtest/gtest.h>
#include <vector>
#include "general-tree.h"
#include "populated_tree.helper.h"

TEST(iterator_class, forEachOperator_ShouldUsePreorderByDefault)
{
	std::vector<int> elements;
	auto order = general_tree<int>::iteration_type::preorder;

	for (int e : populated_tree::tree)
		elements.push_back(e);

	EXPECT_EQ(elements, populated_tree::preorder_vector);
}