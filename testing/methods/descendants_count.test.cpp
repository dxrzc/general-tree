#include <gtest/gtest.h>
#include "general-tree.h"

TEST(descendants_count, throwInvalidArgumentIfNodeIsNull)
{
	general_tree<int> empty_tree;
	general_tree<int>::node null_node = empty_tree.root();
	EXPECT_THROW(empty_tree.descendants_count(null_node), std::invalid_argument);
}

TEST(descendants_count, returnZeroIfNodeIsALeaf)
{
	general_tree<int> empty_tree (1) ;
	general_tree<int>::node root = empty_tree.root();

	EXPECT_EQ(empty_tree.descendants_count(root), 0);
}

TEST(descendants_count, returnTheNumberOfDescendants)
{
	// TODO	
}