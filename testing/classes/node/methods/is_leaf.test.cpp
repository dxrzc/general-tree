#include <gtest/gtest.h>
#include "general-tree.h"

TEST(class_node, is_leaf_ReturnTrueIfNodeIsLeaf)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	EXPECT_TRUE(root.is_leaf());
}

TEST(class_node, is_leaf_ReturnFalseIfNodeIsNotLeaf)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	test_tree.insert_left_child(root, 2);
	EXPECT_FALSE(root.is_leaf());
}