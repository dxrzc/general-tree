#include <gtest/gtest.h>
#include "general_tree.h"

TEST(root_constructor, parentOfRootNodeIsNull)
{
	general_tree<int> tree(1);
	general_tree<int>::node root = tree.root();

	EXPECT_TRUE(root.parent().is_null());	
}

TEST(root_constructor, leftChildOfRootNodeIsNull)
{
    general_tree<int> tree(1);
    general_tree<int>::node root = tree.root();

    EXPECT_TRUE(root.left_child().is_null());
}

TEST(root_constructor, rightSiblingOfRootNodeIsNull)
{
    general_tree<int> tree(1);
    general_tree<int>::node root = tree.root();

    EXPECT_TRUE(root.right_sibling().is_null());
}
