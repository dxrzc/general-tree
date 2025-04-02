#include <gtest/gtest.h>
#include "general-tree.h"
#include "test_resource.helper.h"
#include "populated_tree.helper.h"

class move_constructor : public ::testing::Test
{
	void SetUp() override
	{
		test_resource::reset_calls_count();
	}
};

TEST_F(move_constructor, rhsTreeIsEmptyAfterOperation)
{
    general_tree<int> rhs_tree = populated_tree::create();
    general_tree<int> new_tree(std::move(rhs_tree));

    EXPECT_TRUE(rhs_tree.empty());
}

TEST_F(move_constructor, noElementIsCopiedOrMoved)
{
	general_tree<test_resource> test_tree;
	test_tree.emplace_root("0", 0);
	test_tree.emplace_left_child(test_tree.root(), "1", 1);
	test_tree.emplace_left_child(test_tree.root(), "3", 3);
	test_tree.emplace_right_sibling(test_tree.root().left_child(), "2", 2);

	general_tree<test_resource> new_tree(std::move(test_tree));

	EXPECT_EQ(test_resource::copy_constructor_calls, 0);
	EXPECT_EQ(test_resource::move_constructor_calls, 0);	
}

TEST_F(move_constructor, newTreeIsEqualToTheRhsTree)
{
    general_tree<int> rhs_tree = populated_tree::create();
    auto rhs_tree_copy = rhs_tree;

    general_tree<int> new_tree (std::move(rhs_tree));

    EXPECT_EQ(rhs_tree_copy, new_tree);
}
