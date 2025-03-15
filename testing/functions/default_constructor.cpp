#include <gtest/gtest.h>
#include "general-tree.h"

TEST(default_constructor, parentLeftChildAndRigthSiblingOfRootAreNull)
{
	general_tree<int> tree;
	EXPECT_TRUE(tree.root().parent().is_null());
	EXPECT_TRUE(tree.root().left_child().is_null());
	EXPECT_TRUE(tree.root().right_sibling().is_null());
}