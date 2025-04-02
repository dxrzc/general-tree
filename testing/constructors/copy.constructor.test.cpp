#include <gtest/gtest.h>
#include "general-tree.h"
#include "test_resource.helper.h"

class copy_constructor : public ::testing::Test
{
	void SetUp() override
	{
		test_resource::reset_calls_count();
	}
};

TEST(copy_constructor, doNotModifyTreesIfBothAreEmpty)
{
	general_tree<int> tree;
	general_tree<int> copy = tree;

	EXPECT_TRUE(tree.empty());
	EXPECT_TRUE(copy.empty());
}

TEST(copy_constructor, makeOneCopyPerElement)
{
    general_tree<test_resource> tree;
    std::size_t tree_size = test_resource::populate_tree_resource(tree);

    general_tree<test_resource> copy = tree;

    EXPECT_EQ(test_resource::copy_constructor_calls, tree_size);
    EXPECT_EQ(test_resource::instances_created, tree_size * 2);
}

TEST(copy_constructor, doNotModifyRhsTree)
{
	general_tree<int> tree(0);
	tree.insert_left_child(tree.root(), 1);
	tree.insert_left_child(tree.root(), 2);
	tree.insert_left_child(tree.root().left_child(), 4);
	tree.insert_left_child(tree.root().left_child(), 4);

	std::size_t tree_descendants_count = tree.root().descendants_count();

	general_tree<int> copy = tree;

	EXPECT_EQ(tree.root().descendants_count(), tree_descendants_count);
}

TEST(copy_constructor, treesAreEqualAfterCopy)
{
	general_tree<int> tree(0);
	tree.insert_left_child(tree.root(), 1);
	tree.insert_left_child(tree.root(), 2);
	tree.insert_left_child(tree.root().left_child(), 4);
	tree.insert_left_child(tree.root().left_child(), 4);

	general_tree<int> copy = tree;
	
	EXPECT_EQ(tree, copy);
}
