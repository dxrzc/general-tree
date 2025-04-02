#include <gtest/gtest.h>
#include "general_tree.h"

TEST(clear, callingBeforeDestructorDoesNotCauseFatalFailure)
{
	EXPECT_NO_FATAL_FAILURE({
		general_tree<int> tree;
		tree.create_root(1);
		tree.insert_left_child(tree.root(), 3);
		tree.insert_left_child(tree.root(), 2);
		tree.insert_left_child(tree.root().left_child(), 1000);
		tree.clear();		
	});
}

TEST(clear, rootNullAfterClear)
{
	general_tree<int> tree;
	tree.create_root(1);
	tree.clear();
	EXPECT_TRUE(tree.root().is_null());
}

TEST(clear, callOnEmptyTreeDoesNotModifyTheNullRoot)
{
	general_tree<int> tree;
	tree.clear();
	EXPECT_TRUE(tree.root().is_null());
}
