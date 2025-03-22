#include <gtest/gtest.h>
#include "general-tree.h"

TEST(class_node, child_NodeIsNullptr)
{
	general_tree<int>::node node;
	EXPECT_THROW({
		// block to avoid the warning caused by nodiscard
		auto n = node.child(0);
		},
		std::invalid_argument
	);
}

TEST(class_node, child_IndexZeroReturnsTheFirstChild)
{
	general_tree<int> test_tree(1);
	auto first_child = test_tree.insert_left_child(test_tree.root(), 2);
	test_tree.insert_right_sibling(first_child, 3);

	EXPECT_EQ(test_tree.root().child(0), first_child);
}

TEST(class_node, child_ReturnTheLastChild)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node n = test_tree.root();

	auto first_child = test_tree.insert_left_child(test_tree.root(), 2);
	auto second_child = test_tree.insert_right_sibling(first_child, 3);
	auto third_child = test_tree.insert_right_sibling(second_child, 4);

	const std::size_t index = test_tree.root().children_count();

	EXPECT_EQ(n.child(index - 1), third_child);
}

TEST(class_node, child_ReturnNullNodeIfNodeDoesNotHaveChildrenAndIndexIsZero)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node n = test_tree.root();
	const std::size_t index = 0;

	EXPECT_TRUE(n.child(index).is_null());
}

TEST(class_node, child_ThrowOutOfRangeExceptionIfNodeDoesNotHaveChildrenAndIndexIsNotZero)
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

TEST(class_node, child_ShouldReturnNullNodeIfTheSearchedNodeIsTheOneAfterTheLastChild)
{
	general_tree<int> test_tree(1);
	general_tree<int>::node n = test_tree.root();

	auto first_child = test_tree.insert_left_child(test_tree.root(), 2); // 0
	auto second_child = test_tree.insert_right_sibling(first_child, 3); // 1
	auto third_child = test_tree.insert_right_sibling(second_child, 4); // 2

	const std::size_t index = 3;

	EXPECT_TRUE(n.child(index).is_null());
}