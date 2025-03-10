#include <gtest/gtest.h>
#include "general-tree.h"

TEST(height, throwInvalidArgumentExceptionIfNodeIsNull)
{
	general_tree<int> tree;
	// using a block to avoid the warning caused by nodiscard
	EXPECT_THROW({
			auto height = tree.height(tree.root());
		},
		std::invalid_argument
	);
}

TEST(heigth, returnZeroIfNodeIsALeaf)
{
	general_tree<int> tree(1);
	const std::size_t expected_value = 0;
	EXPECT_EQ(tree.height(tree.root()), expected_value);
}

TEST(heigth, returnOneIfNodeHasChildren)
{
	general_tree<int> tree(1);
	tree.insert_left_child(tree.root(), 2);

	const std::size_t expected_value = 1;
	EXPECT_EQ(tree.height(tree.root()), expected_value);
}

TEST(height, returnTheHeightOfTheTallestBranch)
{
	general_tree<int> tree(1);
	tree.insert_left_child(tree.root(), 2);
	tree.insert_left_child(tree.root().left_child(), 3);
	tree.insert_left_child(tree.root().left_child().left_child(), 4);
	const std::size_t expected_value = 3;
	EXPECT_EQ(tree.height(tree.root()), expected_value);
}
