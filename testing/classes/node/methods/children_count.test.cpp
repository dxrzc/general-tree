#include <gtest/gtest.h>
#include "general_tree.h"

TEST(class_node, children_count_throwInvalidArgumentExceptionIfNodeIsNull)
{
	general_tree<int> tree;
	// using a block to avoid the warning caused by nodiscard
	EXPECT_THROW({
		auto children_count = tree.root().children_count();
		},
		std::invalid_argument
	);
}

TEST(class_node, children_count_returnZeroIfNullDoesNotHaveChildren)
{
	general_tree<int> tree(1);
	const std::size_t expected_value = 0;
	EXPECT_EQ(tree.root().children_count(), expected_value);
}

TEST(class_node, children_count_returnNumberOfChildren)
{
	general_tree<int> tree(1);
	tree.insert_left_child(tree.root(), 2);
	tree.insert_left_child(tree.root(), 3);
	tree.insert_left_child(tree.root(), 4);
	const std::size_t expected_value = 3;
	EXPECT_EQ(tree.root().children_count(), expected_value);
}