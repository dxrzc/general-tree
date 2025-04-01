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

TEST(copy_constructor, noModificationsIfRhsTreeIsEmpty)
{
	general_tree<int> tree;
	general_tree<int> copy = tree;

	EXPECT_TRUE(tree.empty());
	EXPECT_TRUE(copy.empty());
}

TEST(copy_constructor, makeOneCopyPerElement)
{
	general_tree<test_resource> resources;
	resources.emplace_root("0", 0);
	resources.emplace_left_child(resources.root(), "1", 1);
	resources.emplace_right_sibling(resources.root().left_child(), "2", 2);
	resources.emplace_left_child(resources.root().left_child(), "3", 3);
	resources.emplace_right_sibling(resources.root().left_child().left_child(), "4", 4);

	general_tree<test_resource> copy = resources;

	EXPECT_EQ(test_resource::copy_constructor_calls, 5);
	EXPECT_EQ(test_resource::instances_created, 10);
}

TEST(copy_constructor, notModifiesRhsTree)
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