#include <gtest/gtest.h>
#include "general-tree.h"

TEST(class_node, isNull_ReturnTrueIfNodeIsNull)
{
	general_tree<int>::node node;
	EXPECT_TRUE(node.is_null());
}

TEST(class_node, isNull_ReturnFalseIfNodeIsNotNull)
{
	general_tree<int> test_tree(1);
	EXPECT_FALSE(test_tree.root().is_null());
}