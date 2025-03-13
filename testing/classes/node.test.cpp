#include <gtest/gtest.h>
#include "general-tree.h"

TEST(node_class, defaultNodeIsNull)
{
	general_tree<int>::node node;
	EXPECT_TRUE(node.is_null());
}

// equality operator

TEST(node_class, equalityOperator_ReturnTrueIfNodesAreTheSame)
{
	general_tree<int> test_tree(1);
	EXPECT_TRUE(test_tree.root() == test_tree.root());
}

TEST(node_class, equalityOperator_ReturnFalseIfNodesAreDifferent)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	general_tree<int>::node left_child = test_tree.insert_left_child(root, 2);
	EXPECT_FALSE(root == left_child);
}

// left_child

TEST(node_class, leftChild_ReturnLeftChild)
{
	general_tree<int> tree(1);

	const int left_child_value = 2;
	tree.insert_left_child(tree.root(), left_child_value);

	EXPECT_EQ(tree.data(tree.root().left_child()), left_child_value);
}

TEST(node_class, leftChild_ReturnNullNodeIfLeftChildDoesNotExist)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node left_child = test_tree.root().left_child();
	EXPECT_TRUE(left_child.is_null());
}

// parent

TEST(node_class, parent_ReturnTheParent)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node left_child = test_tree.insert_left_child(test_tree.root(), 2);

	EXPECT_EQ(left_child.parent(), test_tree.root());
}

TEST(node_class, parent_ReturnNullNodeIfParentDoesNotExist)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	EXPECT_TRUE(root.parent().is_null());
}

// right_sibling

TEST(node_class, right_sibling_ReturnRightSibling)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	general_tree<int>::node left_child = test_tree.insert_left_child(root, 2);
	general_tree<int>::node right_sibling = test_tree.insert_right_sibling(left_child, 3);

	EXPECT_EQ(left_child.right_sibling(), right_sibling);
}

TEST(node_class, right_sibling_ReturnNullNodeIfRightSiblingDoesNotExist)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	general_tree<int>::node left_child = test_tree.insert_left_child(root, 2);
	EXPECT_TRUE(left_child.right_sibling().is_null());
}

// is_root

TEST(node_class, is_root_ReturnTrueIfNodeIsRoot)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	EXPECT_TRUE(root.is_root());
}

TEST(node_class, is_root_ReturnFalseIfNodeIsNotRoot)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	general_tree<int>::node left_child = test_tree.insert_left_child(root, 2);
	EXPECT_FALSE(left_child.is_root());
}

// is_leaf

TEST(node_class, is_leaf_ReturnTrueIfNodeIsLeaf)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	EXPECT_TRUE(root.is_leaf());
}

TEST(node_class, is_leaf_ReturnFalseIfNodeIsNotLeaf)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	test_tree.insert_left_child(root, 2);
	EXPECT_FALSE(root.is_leaf());
}

// has_right_sibling

TEST(node_class, has_right_sibling_ReturnTrueIfNodeHasRightSibling)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();

	general_tree<int>::node left_child = test_tree.insert_left_child(root, 2);
	general_tree<int>::node right_sibling = test_tree.insert_right_sibling(left_child, 3);

	EXPECT_TRUE(left_child.has_right_sibling());
}

TEST(node_class, has_right_sibling_ReturnFalseIfNodeHasNoRightSibling)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();

	general_tree<int>::node left_child = test_tree.insert_left_child(root, 2);

	EXPECT_FALSE(left_child.has_right_sibling());
}

// has_left_child

TEST(node_class, has_left_child_ReturnTrueIfNodeHasLeftChild)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	test_tree.insert_left_child(root, 2);
	EXPECT_TRUE(root.has_left_child());
}

TEST(node_class, has_left_child_ReturnFalseIfNodeHasNoLeftChild)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node root = test_tree.root();
	EXPECT_FALSE(root.has_left_child());
}

// isNull

TEST(node_class, isNull_ReturnTrueIfNodeIsNull)
{
	general_tree<int>::node node;
	EXPECT_TRUE(node.is_null());
}

TEST(node_class, isNull_ReturnFalseIfNodeIsNotNull)
{
	general_tree<int> test_tree(1);
	EXPECT_FALSE(test_tree.root().is_null());
}

// child

TEST(node_class, child_NodeIsNullptr)
{
	general_tree<int>::node node;
	EXPECT_THROW({
		// block to avoid the warning caused by nodiscard
		auto n = node.child(0);
		},
		std::invalid_argument
	);
}

TEST(node_class, child_IndexZeroReturnsTheFirstChild)
{
	general_tree<int> test_tree(1);
	auto first_child = test_tree.insert_left_child(test_tree.root(), 2);
	test_tree.insert_right_sibling(first_child, 3);

	EXPECT_EQ(test_tree.root().child(0), first_child);
}

TEST(node_class, child_ReturnTheLastChild)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node n = test_tree.root();

	auto first_child = test_tree.insert_left_child(test_tree.root(), 2);
	auto second_child = test_tree.insert_right_sibling(first_child, 3);
	auto third_child = test_tree.insert_right_sibling(second_child, 4);

	const std::size_t index = test_tree.children_count(test_tree.root());

	EXPECT_EQ(n.child(index - 1), third_child);
}

TEST(node_class, child_ReturnNullNodeIfNodeDoesNotHaveChildrenAndIndexIsZero)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node n = test_tree.root();
	const std::size_t index = 0;

	EXPECT_TRUE(n.child(index).is_null());
}

TEST(node_class, child_ThrowOutOfRangeExceptionIfNodeDoesNotHaveChildrenAndIndexIsNotZero)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node n = test_tree.root();
	const std::size_t index = 1;

	EXPECT_THROW({
		// block to avoid the warning caused by nodiscard
		auto x = n.child(index);
		}, 
	std::out_of_range
	);
}

TEST(node_class, child_ShouldReturnNullNodeIfTheSearchedNodeIsTheOneAfterTheLastChild)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node n = test_tree.root();

	auto first_child = test_tree.insert_left_child(test_tree.root(), 2); // 0
	auto second_child = test_tree.insert_right_sibling(first_child, 3); // 1
	auto third_child = test_tree.insert_right_sibling(second_child, 4); // 2

	const std::size_t index = 3;

	EXPECT_TRUE(n.child(index).is_null());
}