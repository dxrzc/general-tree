#include <gtest/gtest.h>
#include "general_tree.h"

TEST(class_node, equalityOperator_ReturnTrueIfNodesAreTheSame)
{
	general_tree<int> test_tree(1);
	EXPECT_TRUE(test_tree.root() == test_tree.root());
}

TEST(class_node, equalityOperator_ReturnFalseIfNodesAreDifferent)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	general_tree<int>::node left_child = test_tree.insert_left_child(root, 2);
	EXPECT_FALSE(root == left_child);
}