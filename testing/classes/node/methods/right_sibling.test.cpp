#include <gtest/gtest.h>
#include "general_tree.h"

TEST(class_node, right_sibling_ReturnRightSibling)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	general_tree<int>::node left_child = test_tree.insert_left_child(root, 2);
	general_tree<int>::node right_sibling = test_tree.insert_right_sibling(left_child, 3);

	EXPECT_EQ(left_child.right_sibling(), right_sibling);
}

TEST(class_node, right_sibling_ReturnNullNodeIfRightSiblingDoesNotExist)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	general_tree<int>::node left_child = test_tree.insert_left_child(root, 2);
	EXPECT_TRUE(left_child.right_sibling().is_null());
}