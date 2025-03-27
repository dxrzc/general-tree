#include <gtest/gtest.h>
#include "general-tree.h"

TEST(iterator_class, assigmentOperator_MustPointToTheSameValue)
{
	const int data = 11313;
	general_tree<int> tree(data);

	general_tree<int>::iterator it1 = tree.begin();
	general_tree<int>::iterator it2;
	it2 = it1;

	EXPECT_EQ(*it1, *it2);
}

TEST(iterator_class, assigmentOperator_MustShareTheSameIterationType)
{
	general_tree<int> tree(11313);

	general_tree<int>::iterator it1 = tree.begin();
	general_tree<int>::iterator it2;
	it2 = it1;

	EXPECT_EQ(it1.iteration_type(), it2.iteration_type());
}