#include <gtest/gtest.h>
#include "general-tree.h"

TEST(class_node, child_ThrowInvalidArgumentIfNodeIsNull)
{
	general_tree<int>::node n = nullptr;
	EXPECT_THROW({ auto ignored = n.child(10); }, std::invalid_argument);
}

TEST(class_node, child_ReturnNullIfChildIsOutOfRange)
{
	general_tree<int> tree(0);
	tree.insert_left_child(tree.root(), 1);
	tree.insert_left_child(tree.root(), 2);
	tree.insert_left_child(tree.root(), 3);

	general_tree<int>::node n = tree.root();

	EXPECT_EQ(n.child(3), nullptr);
}

TEST(class_node, child_ReturnTheExpectedChild)
{
	general_tree<int> tree(0);
	tree.insert_left_child(tree.root(), 1);
	auto expected_child = tree.insert_left_child(tree.root(), 2);
	tree.insert_left_child(tree.root(), 3);

	general_tree<int>::node n = tree.root();

	EXPECT_EQ(n.child(1), expected_child);
}

TEST(class_node, child_ReturnNullIfNodeDoesNotHaveChildren)
{
	general_tree<int> tree(0);
	general_tree<int>::node n = tree.root();

	EXPECT_EQ(n.child(1), nullptr);
}