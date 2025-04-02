#include <gtest/gtest.h>
#include "general_tree.h"

TEST(class_const_iterator, assigmentOperator_iteratorsPointToTheSameNode)
{
	const int data = 11313;
	general_tree<int> tree(data);

	general_tree<int>::const_iterator it1 = tree.cbegin();
	general_tree<int>::const_iterator it2;
	it2 = it1;

	EXPECT_EQ(*it1, *it2);
}

TEST(class_const_iterator, assigmentOperator_iteratorsHaveTheSameIterationType)
{
	general_tree<int> tree(11313);

	general_tree<int>::const_iterator it1 = tree.cbegin();
	general_tree<int>::const_iterator it2;
	it2 = it1;

	EXPECT_EQ(it1.iteration(), it2.iteration());
}

TEST(class_const_iterator, assigmentOperatorByIterator_iteratorsPointToTheSameValue)
{
	const int data = 11313;
	general_tree<int> tree(data);

	general_tree<int>::iterator it1 = tree.begin();
	general_tree<int>::const_iterator it2;
	it2 = it1;

    EXPECT_EQ(*it2, *it1);
}

TEST(class_const_iterator, assigmentOperatorByIterator_iteratorsHaveTheSameIterationType)
{
    const int data = 11313;
    general_tree<int> tree(data);

    general_tree<int>::iterator it1 = tree.begin();
    general_tree<int>::const_iterator it2;
    it2 = it1;

    EXPECT_EQ(it1.iteration(), it2.iteration());
}
