#include <gtest/gtest.h>
#include "general-tree.h"

TEST(root_constructor, rootParentRightSiblingAndLeftChildShouldBeNull)
{
	general_tree<int> tree(1);
	general_tree<int>::node root = tree.root();

	EXPECT_TRUE(root.parent().is_null());
	EXPECT_TRUE(root.right_sibling().is_null());
	EXPECT_TRUE(root.left_child().is_null());
}