#include <gtest/gtest.h>
#include "general_tree.h"

TEST(class_node, height_ThrowInvalidArgumentExceptionIfNodeIsNull)
{
	general_tree<int> tree;
	// using a block to avoid the warning caused by nodiscard
	EXPECT_THROW({
			auto ignored = tree.root().height();
		},
		std::invalid_argument
	);
}

TEST(class_node, height_ReturnZeroIfNodeIsALeaf)
{
	general_tree<int> tree(1);
	EXPECT_EQ(tree.root().height(), 0);
}

TEST(class_node, height_ReturnOneIfNodeHasOneChildren)
{
	general_tree<int> tree(1);
	tree.insert_left_child(tree.root(), 2);

	EXPECT_EQ(tree.root().height(), 1);
}

TEST(class_node, height_ReturnTheHeightOfTheTallestBranch)
{
	general_tree<int> tree(1);
	tree.insert_left_child(tree.root(), 2);
	tree.insert_left_child(tree.root().left_child(), 3);
	tree.insert_left_child(tree.root().left_child().left_child(), 4);

	EXPECT_EQ(tree.root().height(), 3);
}

TEST(class_node, height_ReturnTheHeightOfTheOnlyExistingBranch)
{
	general_tree<int> tree(0);
	auto lc1 = tree.insert_left_child(tree.root(), 1);
	auto lc2 = tree.insert_left_child(lc1, 2);
	auto lc3 = tree.insert_left_child(lc2, 3);
	auto lc4 = tree.insert_left_child(lc3, 4);

	general_tree<int>::node n = tree.root();

	EXPECT_EQ(n.height(), 4);
}
