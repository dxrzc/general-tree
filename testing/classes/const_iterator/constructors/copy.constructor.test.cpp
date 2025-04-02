#include <gtest/gtest.h>
#include "general-tree.h"

TEST(class_const_iterator, copyConstructor_bothIteratorsPointToTheSameValue)
{
	const int data = 11313;
	general_tree<int> tree(data);

	general_tree<int>::const_iterator it1 = tree.cbegin();
	general_tree<int>::const_iterator it2 = it1;

	EXPECT_EQ(*it1, *it2);
}

TEST(class_const_iterator, copyConstructor_bothIteratorsHaveTheSameIterationType)
{
	general_tree<int> tree(11313);

	general_tree<int>::const_iterator it1 = tree.cbegin();
	general_tree<int>::const_iterator it2 = it1;

	EXPECT_EQ(it1.iteration(), it2.iteration());
}
