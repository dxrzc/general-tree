#include <gtest/gtest.h>
#include "general_tree.h"

TEST(class_node, descendants_count_throwInvalidArgumentIfNodeIsNull)
{
	general_tree<int> empty_tree;
	general_tree<int>::node null_node = empty_tree.root();
	EXPECT_THROW({
		auto ignored = null_node.descendants_count();
		},
		std::invalid_argument
	);
}

TEST(class_node, descendants_count_returnZeroIfNodeIsALeaf)
{
	general_tree<int> empty_tree(1);
	general_tree<int>::node root = empty_tree.root();

	EXPECT_EQ(root.descendants_count(), 0);
}

TEST(class_node, descendants_count_returnTheNumberOfDescendants)
{
	general_tree<int> tree(0);
	tree.insert_left_child(tree.root(), 3);
	tree.insert_left_child(tree.root(), 2);
	tree.insert_left_child(tree.root(), 1);
	tree.insert_left_child(tree.root().left_child(), 3);
	tree.insert_left_child(tree.root().left_child(), 2);
	tree.insert_left_child(tree.root().left_child(), 1);
	tree.insert_left_child(tree.root().left_child().right_sibling(), 3);
	tree.insert_left_child(tree.root().left_child().right_sibling(), 2);
	tree.insert_left_child(tree.root().left_child().right_sibling(), 1);	

	general_tree<int>::node root = tree.root();
	
	EXPECT_EQ(root.descendants_count(), 9);
}