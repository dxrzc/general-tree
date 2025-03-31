#include <gtest/gtest.h>
#include "general-tree.h"
#include "test_resource.helper.h"

class delete_right_sibling : public ::testing::Test
{
	void SetUp() override
	{
		test_resource::reset_calls_count();
	}
};

TEST_F(delete_right_sibling, deleteTheLeftChild)
{
	general_tree<int> tree(0);
	auto child = tree.insert_left_child(tree.root(), 1);
	tree.insert_right_sibling(child, 2);

	tree.delete_right_sibling(tree.root().left_child());

	EXPECT_TRUE(child.right_sibling().is_null());
}

TEST_F(delete_right_sibling, deleteRightSiblingAndAllItsNodes)
{
	general_tree<test_resource> tree;
	tree.emplace_root("0", 0);
	auto sibling = tree.emplace_left_child(tree.root(), "1", 1);

	// create a tree
	general_tree<test_resource> right_sibling_tree;
	std::size_t right_sibling_tree_size = test_resource::populate_tree_resource(right_sibling_tree);

	// insert tree as right sibling
	tree.insert_right_sibling(sibling, right_sibling_tree);

	// delete right sibling
	tree.delete_right_sibling(sibling);

	EXPECT_EQ(test_resource::destructor_calls, right_sibling_tree_size);
}

TEST_F(delete_right_sibling, IfRightSiblingWasTheLastSiblingSetTheNewRightSiblingAsNullptr)
{
	// Before: left_sibling -> right_sibling -> nullptr
	// After: left_sibling  -> nullptr

	general_tree<int> tree(0);
	auto left_sibling = tree.insert_left_child(tree.root(), 1);

	// insert right sibling
	tree.insert_right_sibling(left_sibling, 3);

	// delete right sibling
	tree.delete_right_sibling(left_sibling);

	EXPECT_TRUE(left_sibling.right_sibling().is_null());
}

TEST_F(delete_right_sibling, ifRightSiblingWasNotTheLastSiblingSetTheNewRightSibling)
{
	// Before: left_sibling -> right_sibling -> last_sibling
	// After: left_sibling  -> last_sibling

	general_tree<int> tree(0);
	auto left_sibling = tree.insert_left_child(tree.root(), 1);

	// insert right sibling
	tree.insert_right_sibling(left_sibling, 3);

	// insert a right sibling of the right sibling
	auto last_sibling = tree.insert_right_sibling(left_sibling.right_sibling(), 4);

	// delete right sibling
	tree.delete_right_sibling(left_sibling);

	EXPECT_EQ(left_sibling.right_sibling(), last_sibling);
}