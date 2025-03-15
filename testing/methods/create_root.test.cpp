#include <gtest/gtest.h>
#include "general-tree.h"

TEST(create_root, throwRuntimeExceptionIfRootAlreadyExists) {
	general_tree<int> test_tree;
	test_tree.create_root(1);
	EXPECT_THROW(test_tree.create_root(2), std::runtime_error);
}

TEST(create_root, createRootWithGivenData) {
	general_tree<int> test_tree;
	const int root_value = 1;

	test_tree.create_root(root_value);
	EXPECT_EQ(test_tree.data(test_tree.root()), root_value);
}

TEST(create_root, returnANodePointingToRoot)
{
	general_tree<int> test_tree;
	general_tree<int>::node result = test_tree.create_root(1);

	EXPECT_EQ(result, test_tree.root());
}

TEST(create_root, rootParentRightSiblingAndLeftChildShouldBeNull)
{
	general_tree<int> tree;
	tree.create_root(1);

	general_tree<int>::node root = tree.root();
	EXPECT_TRUE(root.parent().is_null());
	EXPECT_TRUE(root.right_sibling().is_null());
	EXPECT_TRUE(root.left_child().is_null());
}