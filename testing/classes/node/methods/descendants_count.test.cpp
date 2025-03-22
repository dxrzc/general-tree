#include <gtest/gtest.h>
#include "general-tree.h"

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

	EXPECT_EQ(empty_tree.root().descendants_count(), 0);
}

TEST(class_node, descendants_count_returnTheNumberOfDescendants)
{
	// TODO	
}