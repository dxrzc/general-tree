#include <gtest/gtest.h>
#include "general_tree.h"

TEST(class_iterator, equalityOperator_returnTrueIfIteratorsPointToTheSameNode)
{
	general_tree<int> tree(0);

	general_tree<int>::iterator it1 = ++tree.begin(general_tree<int>::iteration_type::preorder);
	general_tree<int>::iterator it2 = ++tree.begin(general_tree<int>::iteration_type::preorder);

	EXPECT_TRUE(it1 == it2);
}

TEST(class_iterator, equalityOperator_returnFalseIfIteratorsDoNotPointToTheSameNode)
{
	general_tree<int> tree(0);

	general_tree<int>::iterator it1 = ++tree.begin(general_tree<int>::iteration_type::preorder);
	general_tree<int>::iterator it2 = tree.begin(general_tree<int>::iteration_type::preorder);

	EXPECT_FALSE(it1 == it2);
}

TEST(class_iterator, equalityOperator_returnFalseIfValueInNodeIsTheSameButNodesAreDifferent)
{
    const int value_in_node = 1001;

    general_tree<int> tree(0);
    tree.insert_left_child(tree.root(), value_in_node);
    tree.insert_left_child(tree.root().left_child(), value_in_node);

    // different iterators pointing to nodes that share the same value
    general_tree<int>::iterator left_child_cit = ++tree.begin(general_tree<int>::iteration_type::preorder);
    general_tree<int>::iterator last_child_cit =  ++++tree.begin(general_tree<int>::iteration_type::preorder);

    EXPECT_FALSE(left_child_cit == last_child_cit);
}
