#include <gtest/gtest.h>
#include "populated_tree.helper.h"
#include "test_resource.helper.h"

class assigment_operator : public ::testing::Test
{
    void SetUp() override
    {
        test_resource::reset_calls_count();
    }
};

TEST_F(assigment_operator, noFailureIfBothTreeEmpty)
{
    general_tree<int> left_tree;
    general_tree<int> right_tree;

    EXPECT_NO_FATAL_FAILURE({
        left_tree = right_tree;
    });
}

TEST_F(assigment_operator, noChangesToTreesIfBothTreeEmpty)
{
    general_tree<int> left_tree;
    general_tree<int> right_tree;

    EXPECT_TRUE(left_tree.empty());
    EXPECT_TRUE(right_tree.empty());
}

TEST_F(assigment_operator, noCopiesAreMadeIfWeAreAssigningTheSameTree)
{
    general_tree<test_resource> tree;
    tree.emplace_root("0", 1);
    tree.emplace_left_child(tree.root(), "1", 1);

    tree = tree;

    EXPECT_EQ(test_resource::copy_constructor_calls, 0);
}

TEST_F(assigment_operator, deletePreviousElementsInTree)
{
    general_tree<test_resource> tree;
    std::size_t tree_size =  test_resource::populate_tree_resource(tree);

    general_tree<test_resource> new_tree;
    new_tree.emplace_root("0",0);
    new_tree.emplace_left_child(new_tree.root(), "1", 1);

    tree = new_tree;

    EXPECT_EQ(test_resource::destructor_calls, tree_size);
}

TEST_F(assigment_operator, treesAreEqualAfterAssigment)
{
    general_tree<int> tree;
    tree.create_root(0);
    tree.emplace_left_child(tree.root(), 1);

    general_tree<int> new_tree = populated_tree::create();

    tree = new_tree;

    EXPECT_EQ(tree, new_tree);
}

TEST_F(assigment_operator, noChangesToRhsTree)
{
    general_tree<int> right_tree(1);
    right_tree.insert_left_child(right_tree.root(), 3);
    right_tree.insert_left_child(right_tree.root(), 2);
    right_tree.insert_left_child(right_tree.root().left_child(), 4);

    // save the rhs tree state
    auto right_tree_copy = right_tree;

    general_tree<int> left_tree (1);
    left_tree = right_tree;

    EXPECT_EQ(right_tree_copy, right_tree);
}
