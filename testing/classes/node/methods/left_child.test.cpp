#include <gtest/gtest.h>
#include "general-tree.h"

TEST(class_node, leftChild_ReturnLeftChild)
{
	general_tree<int> tree(1);

	const int left_child_value = 2;
	tree.insert_left_child(tree.root(), left_child_value);

	EXPECT_EQ(tree.data(tree.root().left_child()), left_child_value);
}

TEST(class_node, leftChild_ReturnNullNodeIfLeftChildDoesNotExist)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node left_child = test_tree.root().left_child();
	EXPECT_TRUE(left_child.is_null());
}