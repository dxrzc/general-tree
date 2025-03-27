#include <gtest/gtest.h>
#include "general-tree.h"

TEST(iterator_class, desreferenceOperator_ReturnDataInNode)
{
	const int data = 11313;
	general_tree<int> tree(data);
	general_tree<int>::iterator it = tree.begin(general_tree<int>::iteration_type::preorder);

	EXPECT_EQ(*it, data);
}