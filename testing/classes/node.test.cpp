#include <gtest/gtest.h>
#include "general-tree.h"

TEST(Node, defaultNodeIsNull)
{
	general_tree<int>::node node;
	EXPECT_TRUE(node.is_null());
}

// left_child

TEST(Node, leftChild_ReturnLeftChild)
{
	general_tree<int> tree(1);

	const int left_child_value = 2;
	tree.insert_left_child(tree.root(), left_child_value);

	EXPECT_EQ(tree.data(tree.root().left_child()), left_child_value);
}

TEST(Node, leftChild_ReturnNullNodeIfLeftChildDoesNotExist)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node left_child = test_tree.root().left_child();
	EXPECT_TRUE(left_child.is_null());
}

// parent

TEST(Node, parent_ReturnTheParent)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node left_child = test_tree.insert_left_child(test_tree.root(), 2);

	EXPECT_EQ(left_child.parent(), test_tree.root());
}

TEST(Node, parent_ReturnNullNodeIfParentDoesNotExist)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	EXPECT_TRUE(root.parent().is_null());
}

// right_sibling

TEST(Node, right_sibling_ReturnRightSibling)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	general_tree<int>::node left_child = test_tree.insert_left_child(root, 2);
	general_tree<int>::node right_sibling = test_tree.insert_right_sibling(left_child, 3);

	EXPECT_EQ(left_child.right_sibling(), right_sibling);
}

TEST(Node, right_sibling_ReturnNullNodeIfRightSiblingDoesNotExist)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	general_tree<int>::node left_child = test_tree.insert_left_child(root, 2);
	EXPECT_TRUE(left_child.right_sibling().is_null());
}

// is_root

TEST(Node, is_root_ReturnTrueIfNodeIsRoot)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	EXPECT_TRUE(root.is_root());
}

TEST(Node, is_root_ReturnFalseIfNodeIsNotRoot)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	general_tree<int>::node left_child = test_tree.insert_left_child(root, 2);
	EXPECT_FALSE(left_child.is_root());
}

// is_leaf

TEST(Node, is_leaf_ReturnTrueIfNodeIsLeaf)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	EXPECT_TRUE(root.is_leaf());
}

TEST(Node, is_leaf_ReturnFalseIfNodeIsNotLeaf)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	test_tree.insert_left_child(root, 2);
	EXPECT_FALSE(root.is_leaf());
}

// has_right_sibling

TEST(Node, has_right_sibling_ReturnTrueIfNodeHasRightSibling)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();

	general_tree<int>::node left_child = test_tree.insert_left_child(root, 2);
	general_tree<int>::node right_sibling = test_tree.insert_right_sibling(left_child, 3);

	EXPECT_TRUE(left_child.has_right_sibling());
}

TEST(Node, has_right_sibling_ReturnFalseIfNodeHasNoRightSibling)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();

	general_tree<int>::node left_child = test_tree.insert_left_child(root, 2);

	EXPECT_FALSE(left_child.has_right_sibling());
}

// has_left_child

TEST(Node, has_left_child_ReturnTrueIfNodeHasLeftChild)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	test_tree.insert_left_child(root, 2);
	EXPECT_TRUE(root.has_left_child());
}

TEST(Node, has_left_child_ReturnFalseIfNodeHasNoLeftChild)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	EXPECT_FALSE(root.has_left_child());
}

// isNull

TEST(Node, isNull_ReturnTrueIfNodeIsNull)
{
	general_tree<int>::node node;
	EXPECT_TRUE(node.is_null());
}

TEST(Node, isNull_ReturnFalseIfNodeIsNotNull)
{
	general_tree<int> test_tree(1);
	EXPECT_FALSE(test_tree.root().is_null());
}