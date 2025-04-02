#include <gtest/gtest.h>
#include "general_tree.h"

TEST(empty, returnTrueIfTreeIsEmpty)
{
	general_tree<int> test_tree;
	EXPECT_TRUE(test_tree.empty());
}

TEST(empty, returnFalseIfTreeNotEmpty)
{
	general_tree<int> test_tree;
	test_tree.create_root(1);
	EXPECT_FALSE(test_tree.empty());
}