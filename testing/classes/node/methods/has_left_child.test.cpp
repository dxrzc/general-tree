#include <gtest/gtest.h>
#include "general-tree.h"

TEST(class_node, has_left_child_ReturnTrueIfNodeHasLeftChild)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	test_tree.insert_left_child(root, 2);
	EXPECT_TRUE(root.has_left_child());
}

TEST(class_node, has_left_child_ReturnFalseIfNodeHasNoLeftChild)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	EXPECT_FALSE(root.has_left_child());
}
