#include <gtest/gtest.h>
#include "general-tree.h"

TEST(iterator_class, equalityOperator_ReturnTrueIfPointingToTheSameValue)
{
	general_tree<int> tree(0);

	general_tree<int>::iterator it1 = ++tree.begin(general_tree<int>::iteration_type::preorder);
	general_tree<int>::iterator it2 = ++tree.begin(general_tree<int>::iteration_type::preorder);

	EXPECT_TRUE(it1 == it2);
}

TEST(iterator_class, equalityOperator_ReturnFalseIfNotPointingToTheSameValue)
{
	general_tree<int> tree(0);

	general_tree<int>::iterator it1 = ++tree.begin(general_tree<int>::iteration_type::preorder);
	general_tree<int>::iterator it2 = tree.begin(general_tree<int>::iteration_type::preorder);

	EXPECT_FALSE(it1 == it2);
}