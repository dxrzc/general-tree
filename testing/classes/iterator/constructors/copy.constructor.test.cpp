#include <gtest/gtest.h>
#include "general_tree.h"

TEST(class_iterator, copyConstructor_iteratorsPointToTheSameValue)
{
	const int data = 11313;
	general_tree<int> tree(data);

	general_tree<int>::iterator it1 = tree.begin();
	general_tree<int>::iterator it2 = it1;

	EXPECT_EQ(*it1, *it2);
}

TEST(class_iterator, copyConstructor_iteratorsHaveTheSameIterationType)
{	
	general_tree<int> tree(11313);

	general_tree<int>::iterator it1 = tree.begin();
	general_tree<int>::iterator it2 = it1;

    EXPECT_EQ(it1.iteration(), it2.iteration());
}
