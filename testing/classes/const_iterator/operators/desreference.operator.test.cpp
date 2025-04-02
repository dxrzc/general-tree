#include <gtest/gtest.h>
#include "general-tree.h"

TEST(class_const_iterator, desreferenceOperator_returnDataInNode)
{
    const int data = 11313;

    general_tree<int> tree(0);
    tree.insert_left_child(tree.root(), data);

    general_tree<int>::const_iterator cit = ++tree.cbegin(general_tree<int>::iteration_type::preorder);
    EXPECT_EQ(*cit, data);
}
