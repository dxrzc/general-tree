#include <gtest/gtest.h>
#include "general_tree.h"

TEST(default_constructor, rootIsNull)
{
	general_tree<int> tree;
	EXPECT_TRUE(tree.root().is_null());
}