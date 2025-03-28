#include <gtest/gtest.h>
#include <vector>
#include "general-tree.h"
#include "populated_tree.helper.h"

TEST(class_const_iterator, preIncrementOperator_ReturnIteratorToTheNextValue)
{
	general_tree<int> tree(1);
	const int next = 100;
	tree.insert_left_child(tree.root(), next);

	general_tree<int>::const_iterator it = tree.cbegin(general_tree<int>::iteration_type::preorder);
	general_tree<int>::const_iterator advanced = ++it;

	EXPECT_EQ(*advanced, 100);
}

TEST(class_const_iterator, preIncrementOperator_MatchExpectedPreorderTraversal)
{
	std::vector<int> elements;
	auto order = general_tree<int>::iteration_type::preorder;

	for (auto it = populated_tree::tree.cbegin(order); it != populated_tree::tree.cend(); ++it)
		elements.push_back(*it);

	EXPECT_EQ(elements, populated_tree::preorder_vector);
}

TEST(class_const_iterator, preIncrementOperator_MatchExpectedPostOrderTraversal)
{
	std::vector<int> elements;
	auto order = general_tree<int>::iteration_type::postorder;

	for (auto it = populated_tree::tree.cbegin(order); it != populated_tree::tree.cend(); ++it)
		elements.push_back(*it);

	EXPECT_EQ(elements, populated_tree::postorder_vector);
}