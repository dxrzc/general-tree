#include <gtest/gtest.h>
#include <vector>
#include "general-tree.h"
#include "populated_tree.helper.h"

TEST(class_iterator, postIncrementOperator_returnIteratorToTheCurrentValue)
{
    const int root = 1232332;
    general_tree<int> tree(root);

    tree.insert_left_child(tree.root(), 100);

	general_tree<int>::iterator it = tree.begin(general_tree<int>::iteration_type::preorder);
	general_tree<int>::iterator before_advance= it++;

	EXPECT_EQ(*before_advance, root);
}

TEST(class_iterator, postIncrementOperator_preorderTraversal)
{
	general_tree<int> test_tree = populated_tree::create();

	std::vector<int> elements;
	auto order = general_tree<int>::iteration_type::preorder;

	for (auto it = test_tree.begin(order); it != test_tree.end(); it++)
		elements.push_back(*it);

	EXPECT_EQ(elements, populated_tree::preorder_vector);
}

TEST(class_iterator, postIncrementOperator_postOrderTraversal)
{
	general_tree<int> test_tree = populated_tree::create();

	std::vector<int> elements;
	auto order = general_tree<int>::iteration_type::postorder;

	for (auto it = test_tree.begin(order); it != test_tree.end(); it++)
		elements.push_back(*it);

	EXPECT_EQ(elements, populated_tree::postorder_vector);
}
