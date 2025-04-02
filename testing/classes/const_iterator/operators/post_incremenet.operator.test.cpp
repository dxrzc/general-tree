#include <gtest/gtest.h>
#include <vector>
#include "general-tree.h"
#include "populated_tree.helper.h"

TEST(class_const_iterator, postIncrementOperator_returnIteratorToTheCurrentValue)
{
    const int root_value = 1;
    general_tree<int> tree(root_value);

    tree.insert_left_child(tree.root(), 100);

	general_tree<int>::const_iterator it = tree.cbegin(general_tree<int>::iteration_type::preorder);
	general_tree<int>::const_iterator before_advance = it++;

    EXPECT_EQ(*before_advance, root_value);
}

TEST(class_const_iterator, postIncrementOperator_preorderTraversal)
{
	general_tree<int> test_tree = populated_tree::create();

	std::vector<int> elements;
	auto order = general_tree<int>::iteration_type::preorder;

	for (auto it = test_tree.cbegin(order); it != test_tree.cend(); it++)
		elements.push_back(*it);

	EXPECT_EQ(elements, populated_tree::preorder_vector);
}

TEST(class_const_iterator, postIncrementOperator_postorderTraversal)
{
	general_tree<int> test_tree = populated_tree::create();

	std::vector<int> elements;
	auto order = general_tree<int>::iteration_type::postorder;

	for (auto it = test_tree.cbegin(order); it != test_tree.cend(); it++)
		elements.push_back(*it);

	EXPECT_EQ(elements, populated_tree::postorder_vector);
}
