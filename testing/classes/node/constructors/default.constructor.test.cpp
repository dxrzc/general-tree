#include <gtest/gtest.h>
#include "general_tree.h"

TEST(class_node, defaultConstructor_NodeIsNull)
{
	general_tree<int>::node node;
	EXPECT_TRUE(node.is_null());
}