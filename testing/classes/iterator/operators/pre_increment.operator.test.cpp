#include <gtest/gtest.h>
#include <vector>
#include "general-tree.h"
#include "populated_tree.helper.h"

TEST(iterator_class, preIncrementOperator_ReturnIteratorToTheNextValue)
{
	general_tree<int> tree (1);
	const int next = 100;
	tree.insert_left_child(tree.root(), next);

	general_tree<int>::iterator it = tree.begin(general_tree<int>::iteration_type::preorder);
	general_tree<int>::iterator advanced = ++it;

	EXPECT_EQ(*advanced, 100);
}

TEST(iterator_class, preIncrementOperator_MatchExpectedPreorderTraversal)
{	
	general_tree<int> test_tree = populated_tree::create();

	std::vector<int> elements;	
	auto order = general_tree<int>::iteration_type::preorder;

	for (auto it = test_tree.begin(order); it != test_tree.end(); ++it)
		elements.push_back(*it);

	EXPECT_EQ(elements, populated_tree::preorder_vector);
}

TEST(iterator_class, preIncrementOperator_MatchExpectedPostOrderTraversal)
{
	general_tree<int> test_tree = populated_tree::create();

	std::vector<int> elements;
	auto order = general_tree<int>::iteration_type::postorder;

	for (auto it = test_tree.begin(order); it != test_tree.end(); ++it)
		elements.push_back(*it);

	EXPECT_EQ(elements, populated_tree::postorder_vector);
}