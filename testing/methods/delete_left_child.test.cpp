#include <gtest/gtest.h>
#include "test_resource.helper.h"

class delete_left_child : public ::testing::Test
{
	void SetUp() override
	{
		test_resource::reset_calls_count();
	}
};

TEST_F(delete_left_child, deleteTheLeftChild)
{
	general_tree<int> tree (0);	
	tree.insert_left_child(tree.root(), 1);
	
	tree.delete_left_child(tree.root());

	EXPECT_TRUE(tree.root().left_child().is_null());
}

TEST_F(delete_left_child, deleteLeftChildAndAllItsNodes)
{
	general_tree<test_resource> tree;
	tree.emplace_root("0", 0);
	general_tree<test_resource>::node parent_node = tree.root();
	
	// create a tree
	general_tree<test_resource> left_child_tree;
	std::size_t left_tree_size = test_resource::populate_tree_resource(left_child_tree);

	// insert tree as left child
	tree.insert_left_child(parent_node, left_child_tree);

	// delete all the nodes from the inserted tree
	tree.delete_left_child(parent_node);

	EXPECT_EQ(test_resource::destructor_calls, left_tree_size);
}

TEST_F(delete_left_child, parentLeftChildIsNowNull)
{
	// Before:
	/*
	   parent 
	   /
      left_child -> nullptr

	*/

	// After:
	/*
	
		parent
	   /
	  nullptr

	*/


	general_tree<int> tree(1);
	general_tree<int>::node parent_node = tree.root();

	// insert a left child
	tree.insert_left_child(parent_node, 2);
	
	// delete it
	tree.delete_left_child(parent_node);

	EXPECT_TRUE(parent_node.left_child().is_null());
}

TEST_F(delete_left_child, parentLeftChildIsNowTheNextChildren)
{
	// Before:
	/*
	   parent
	   /
	  left_child -> right_sibling

	*/

	// After:
	/*

		parent
	   /
	  right_sibling

	*/


	general_tree<int> tree(1);
	general_tree<int>::node parent_node = tree.root();

	auto left_child = tree.insert_left_child(parent_node, 2);

	// this should be the new left child after the deletion
	auto right_sibling = tree.insert_right_sibling(left_child, 3);

	// delete left child
	tree.delete_left_child(parent_node);

	EXPECT_EQ(parent_node.left_child(), right_sibling);	
}
