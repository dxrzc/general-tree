#include <gtest/gtest.h>
#include "general-tree.h"

TEST(Node, defaultNodeIsNull)
{
	general_tree<int>::node node;
	EXPECT_TRUE(node.is_null());
}

// equality operator

TEST(Node, equalityOperator_returnTrueIfNodesAreEqual)
{
	general_tree<int> tree(1);
	general_tree<int>::node lhs = tree.root();
	general_tree<int>::node rhs = tree.root();
	EXPECT_TRUE(lhs == rhs);
}

TEST(Node, equalityOperator_returnFalseIfNodesAreNotEqual)
{
	general_tree<int> tree(1);
	general_tree<int>::node lhs = tree.root();
	general_tree<int>::node rhs(2);
	EXPECT_FALSE(lhs == rhs);
}

// inequality operator

TEST(Node, inequalityOperator_returnTrueIfNodesAreNotEqual)
{
	general_tree<int> tree(1);
	general_tree<int>::node lhs = tree.root();
	general_tree<int>::node rhs(2);
	EXPECT_TRUE(lhs != rhs);
}

TEST(Node, inequalityOperator_returnFalseIfNodesAreEqual)
{
	general_tree<int> tree(1);
	general_tree<int>::node lhs = tree.root();
	general_tree<int>::node rhs = tree.root();
	EXPECT_FALSE(lhs != rhs);
}

// boolean operator

TEST(Node, booleanOperator_returnTrueIfNodeIsNotNull)
{
	general_tree<int> tree(1);
	general_tree<int>::node node = tree.root();
	EXPECT_TRUE(node);
}

TEST(Node, booleanOperator_returnFalseIfNodeIsNull)
{
	general_tree<int> empty_tree;
	general_tree<int>::node node = empty_tree.root();
	EXPECT_FALSE(node);
}

// greater than operator

TEST(Node, greaterThanOperator_ReturnTrueIfRhsNodeValueIsGreater)
{
	general_tree<int> tree(1);
	general_tree<int>::node lhs = tree.root();
	general_tree<int>::node rhs(2);
	EXPECT_TRUE(rhs > lhs);
}

TEST(Node, greaterThanOperator_ReturnFalseIfRhsNodeValueIsLess)
{
	general_tree<int> tree(1);
	general_tree<int>::node lhs = tree.root();
	general_tree<int>::node rhs(0);
	EXPECT_FALSE(rhs > lhs);
}

// greater than or equal operator

TEST(Node, greaterThanOrEqualOperator_ReturnTrueIfRhsNodeValueIsGreater)
{
	general_tree<int> tree(1);
	general_tree<int>::node lhs = tree.root();
	general_tree<int>::node rhs(2);
	EXPECT_TRUE(rhs >= lhs);
}

TEST(Node, greaterThanOrEqualOperator_ReturnTrueIfRhsNodeValueIsEqual)
{
	general_tree<int> tree(1);
	general_tree<int>::node lhs = tree.root();
	general_tree<int>::node rhs = tree.root();
	EXPECT_TRUE(rhs >= lhs);
}

// less than operator

TEST(Node, lessThanOperator_ReturnTrueIfRhsNodeValueIsLess)
{
	general_tree<int> tree(1);
	general_tree<int>::node lhs = tree.root();
	general_tree<int>::node rhs(0);
	EXPECT_TRUE(rhs < lhs);
}

TEST(Node, lessThanOperator_ReturnFalseIfRhsNodeValueIsGreater)
{
	general_tree<int> tree(1);
	general_tree<int>::node lhs = tree.root();
	general_tree<int>::node rhs(2);
	EXPECT_FALSE(rhs < lhs);
}

// less than or equal operator

TEST(Node, lessThanOrEqualOperator_ReturnTrueIfRhsNodeValueIsLess)
{
	general_tree<int> tree(1);
	general_tree<int>::node lhs = tree.root();
	general_tree<int>::node rhs(0);
	EXPECT_TRUE(rhs <= lhs);
}

TEST(Node, lessThanOrEqualOperator_ReturnTrueIfRhsNodeValueIsEqual)
{
	general_tree<int> tree(1);
	general_tree<int>::node lhs = tree.root();
	general_tree<int>::node rhs = tree.root();
	EXPECT_TRUE(rhs <= lhs);
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

// child

TEST(Node, child_NodeIsNullptr)
{
	general_tree<int>::node node;
	EXPECT_THROW({
		// block to avoid the warning caused by nodiscard
		auto n = node.child(0);
		},
		std::invalid_argument
	);
}

TEST(Node, child_IndexZeroReturnsTheFirstChild)
{
	general_tree<int> test_tree(1);
	auto first_child = test_tree.insert_left_child(test_tree.root(), 2);
	test_tree.insert_right_sibling(first_child, 3);

	EXPECT_EQ(test_tree.root().child(0), first_child);
}

TEST(Node, child_ReturnTheLastChild)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node n = test_tree.root();

	auto first_child = test_tree.insert_left_child(test_tree.root(), 2);
	auto second_child = test_tree.insert_right_sibling(first_child, 3);
	auto third_child = test_tree.insert_right_sibling(second_child, 4);

	const std::size_t index = test_tree.children_count(test_tree.root());

	EXPECT_EQ(n.child(index - 1), third_child);
}

TEST(Node, child_ReturnNullNodeIfNodeDoesNotHaveChildrenAndIndexIsZero)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node n = test_tree.root();
	const std::size_t index = 0;

	EXPECT_TRUE(n.child(index).is_null());
}

TEST(Node, child_ThrowOutOfRangeExceptionIfNodeDoesNotHaveChildrenAndIndexIsNotZero)
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

TEST(Node, child_ShouldReturnNullNodeIfTheSearchedNodeIsTheOneAfterTheLastChild)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node n = test_tree.root();

	auto first_child = test_tree.insert_left_child(test_tree.root(), 2); // 0
	auto second_child = test_tree.insert_right_sibling(first_child, 3); // 1
	auto third_child = test_tree.insert_right_sibling(second_child, 4); // 2

	const std::size_t index = 3;

	EXPECT_TRUE(n.child(index).is_null());
}