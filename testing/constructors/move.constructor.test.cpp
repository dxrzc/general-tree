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

TEST_F(move_constructor, rhsTreeRemainsEmpty)
{
	general_tree<int> test_tree = populated_tree::create();
	general_tree<int> new_tree(std::move(test_tree));

	EXPECT_TRUE(test_tree.empty());
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

TEST_F(move_constructor, treeContainsAllTheNodesAfterOperation)
{
	general_tree<int> test_tree = populated_tree::create();
	std::size_t test_tree_size= test_tree.root().descendants_count() + 1;

	general_tree<int> new_tree(std::move(test_tree));
	std::size_t new_tree_size = new_tree.root().descendants_count() + 1;

	EXPECT_EQ(new_tree_size, test_tree_size);
}

