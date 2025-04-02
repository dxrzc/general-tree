#include <gtest/gtest.h>
#include "general_tree.h"

TEST(class_node, is_root_ReturnTrueIfNodeIsRoot)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	EXPECT_TRUE(root.is_root());
}

TEST(class_node, is_root_ReturnFalseIfNodeIsNotRoot)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	general_tree<int>::node left_child = test_tree.insert_left_child(root, 2);
	EXPECT_FALSE(left_child.is_root());
}