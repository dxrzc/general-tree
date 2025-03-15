#include <gtest/gtest.h>
#include "general-tree.h"

TEST(class_node, parent_ReturnTheParent)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node left_child = test_tree.insert_left_child(test_tree.root(), 2);

	EXPECT_EQ(left_child.parent(), test_tree.root());
}

TEST(class_node, parent_ReturnNullNodeIfParentDoesNotExist)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	EXPECT_TRUE(root.parent().is_null());
}