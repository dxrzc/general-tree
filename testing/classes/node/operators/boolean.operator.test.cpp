#include <gtest/gtest.h>
#include "general-tree.h"

TEST(class_node, booleanOperator_ReturnTrueIfNodeIsNotNull)
{
	general_tree<int> test_tree(1);
	EXPECT_TRUE(test_tree.root());
}

TEST(class_node, booleanOperator_ReturnFalseIfNodeIsNull)
{
	general_tree<int>::node node;
	EXPECT_FALSE(node);
}