#include <gtest/gtest.h>
#include "general-tree.h"

TEST(children_count, throwInvalidArgumentExceptionIfNodeIsNull)
{
	general_tree<int> tree;
	// using a block to avoid the warning caused by nodiscard
	EXPECT_THROW({
		auto children_count = tree.children_count(tree.root());
		}, 
		std::invalid_argument
	);
}

TEST(children_count, returnZeroIfNullDoesNotHaveChildren)
{
	general_tree<int> tree(1);
	const std::size_t expected_value = 0;
	EXPECT_EQ(tree.children_count(tree.root()), expected_value);
}

TEST(children_count, returnNumberOfChildren)
{
	general_tree<int> tree(1);
	tree.insert_left_child(tree.root(), 2);
	tree.insert_left_child(tree.root(), 3);
	tree.insert_left_child(tree.root(), 4);
	const std::size_t expected_value = 3;
	EXPECT_EQ(tree.children_count(tree.root()), expected_value);
}