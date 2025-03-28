#include <gtest/gtest.h>
#include "general-tree.h"

TEST(class_const_iterator, desreferenceOperator_ReturnDataInNode)
{
	const int data = 11313;
	general_tree<int> tree(data);
	general_tree<int>::const_iterator it = tree.cbegin(general_tree<int>::iteration_type::preorder);

	EXPECT_EQ(*it, data);
}