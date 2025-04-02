#include <gtest/gtest.h>
#include "general-tree.h"

TEST(class_const_iterator, equalityOperator_returnTrueIfIteratorsPointToTheSameNode)
{
	general_tree<int> tree(0);

	general_tree<int>::const_iterator it1 = ++tree.cbegin(general_tree<int>::iteration_type::preorder);
	general_tree<int>::const_iterator it2 = ++tree.cbegin(general_tree<int>::iteration_type::preorder);

	EXPECT_TRUE(it1 == it2);
}

TEST(class_const_iterator, equalityOperator_returnTrueIfIteratorsDoNotPointToTheSameNode)
{
	general_tree<int> tree(0);

	general_tree<int>::const_iterator it1 = ++tree.cbegin(general_tree<int>::iteration_type::preorder);
	general_tree<int>::const_iterator it2 = tree.cbegin(general_tree<int>::iteration_type::preorder);

	EXPECT_FALSE(it1 == it2);
}

TEST(class_const_iterator, equalityOperator_returnFalseIfValueInNodeIsTheSameButNodesAreDifferent)
{
    const int value_in_node = 1001;

    general_tree<int> tree(0);
    tree.insert_left_child(tree.root(), value_in_node);
    tree.insert_left_child(tree.root().left_child(), value_in_node);

    // different iterators pointing to nodes that share the same value
    general_tree<int>::const_iterator left_child_cit = ++tree.cbegin(general_tree<int>::iteration_type::preorder);
    general_tree<int>::const_iterator last_child_cit =  ++++tree.cbegin(general_tree<int>::iteration_type::preorder);

    EXPECT_FALSE(left_child_cit == last_child_cit);
}

TEST(class_const_iterator, equalityOperator_canWorkWithIterators)
{
    general_tree<int> tree(0);
    tree.insert_left_child(tree.root(), 1);

    general_tree<int>::const_iterator cit = tree.cbegin(general_tree<int>::iteration_type::preorder);
    general_tree<int>::const_iterator it = tree.begin(general_tree<int>::iteration_type::preorder);

    EXPECT_EQ(cit, it);

    ++cit;

    EXPECT_FALSE(cit == it);
}
