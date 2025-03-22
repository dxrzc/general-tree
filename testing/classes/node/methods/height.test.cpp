#include <gtest/gtest.h>
#include "general-tree.h"

TEST(class_node, height_throwInvalidArgumentExceptionIfNodeIsNull)
{
	general_tree<int> tree;
	// using a block to avoid the warning caused by nodiscard
	EXPECT_THROW({
			auto ignored = tree.root().height();
		},
		std::invalid_argument
	);
}

TEST(class_node, height_returnZeroIfNodeIsALeaf)
{
	general_tree<int> tree(1);
	const std::size_t expected_value = 0;
	EXPECT_EQ(tree.root().height(), expected_value);
}

TEST(class_node, height_returnOneIfNodeHasChildren)
{
	general_tree<int> tree(1);
	tree.insert_left_child(tree.root(), 2);

	const std::size_t expected_value = 1;
	EXPECT_EQ(tree.root().height(), expected_value);
}

TEST(class_node, height_returnTheHeightOfTheTallestBranch)
{
	general_tree<int> tree(1);
	tree.insert_left_child(tree.root(), 2);
	tree.insert_left_child(tree.root().left_child(), 3);
	tree.insert_left_child(tree.root().left_child().left_child(), 4);
	const std::size_t expected_value = 3;
	EXPECT_EQ(tree.root().height(), expected_value);
}
