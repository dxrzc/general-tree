#include <gtest/gtest.h>
#include "general-tree.h"
#include "populated_tree.helper.h"

TEST(equalityOperator, returnTrueIfBothTreeAreEmpty)
{
	general_tree<int> tree1;
	general_tree<int> tree2;
	EXPECT_TRUE(tree1 == tree2);
}

TEST(equalityOperator, returnFalseIfLeftTreeIsEmptyAndRightTreeIsNot)
{
	general_tree<int> left_tree;
	general_tree<int> right_tree (1);
	EXPECT_FALSE(left_tree == right_tree);
}

TEST(equalityOperator, returnFalseIfRightTreeIsEmptyAndLeftTreeIsNot)
{
	general_tree<int> left_tree(1);
	general_tree<int> right_tree;
	EXPECT_FALSE(left_tree == right_tree);
}

TEST(equalityOperator, returnTrueIfRightTreeIsTheSameTree)
{
	general_tree<int> tree;
	EXPECT_TRUE(tree == tree);
}

TEST(equalityOperator, returnTrueIfTreesContainsTheSameRootValueAndOnlyContainsOneNode)
{
	const int root_value = 14244;
	general_tree<int> left_tree(root_value);
	general_tree<int> right_tree(root_value);

	EXPECT_TRUE(left_tree == right_tree);
}

TEST(equalityOperator, returnFalseIfTreesDoNotContainsTheSameRootValueAndOnlyContainsOneNode)
{	
	general_tree<int> left_tree(100);
	general_tree<int> right_tree(101);

	EXPECT_FALSE(left_tree == right_tree);
}

TEST(equalityOperator, returnFalseIfTreesAreNotEqualDifferentStructure)
{
    general_tree<int> left_tree;
    auto root1 = left_tree.create_root(1);
    auto child1 = left_tree.insert_left_child(root1, 2);
    left_tree.insert_left_child(child1, 3);

    general_tree<int> right_tree;
    auto root2 = right_tree.create_root(1);
    auto child2 = right_tree.insert_left_child(root2, 2);
    right_tree.insert_left_child(child2, 4); // Different value

    EXPECT_FALSE(left_tree == right_tree);
}

TEST(equalityOperator, returnFalseIfTreesHaveDifferentDataButSameStructure)
{
    general_tree<int> left_tree;
    auto root1 = left_tree.create_root(1);
    auto child1 = left_tree.insert_left_child(root1, 2);
    auto sibling1 = left_tree.insert_right_sibling(child1, 3);

    general_tree<int> right_tree;
    auto root2 = right_tree.create_root(1);
    auto child2 = right_tree.insert_left_child(root2, 5); // Different value
    auto sibling2 = right_tree.insert_right_sibling(child2, 3);

    EXPECT_FALSE(left_tree == right_tree);
}

TEST(equalityOperator, returnFalseIfLeftTreeHasMoreChildren)
{
    general_tree<int> left_tree;
    auto root1 = left_tree.create_root(10);
    auto child1 = left_tree.insert_left_child(root1, 20);
    left_tree.insert_right_sibling(child1, 30);

    general_tree<int> right_tree;
    auto root2 = right_tree.create_root(10);
    right_tree.insert_left_child(root2, 20); // Missing sibling

    EXPECT_FALSE(left_tree == right_tree);
}

TEST(equalityOperator, returnFalseIfRightTreeHasMoreChildren)
{
    general_tree<int> left_tree;
    auto root1 = left_tree.create_root(50);
    auto child1 = left_tree.insert_left_child(root1, 60);

    general_tree<int> right_tree;
    auto root2 = right_tree.create_root(50);
    auto child2 = right_tree.insert_left_child(root2, 60);
    right_tree.insert_right_sibling(child2, 70); // Extra node

    EXPECT_FALSE(left_tree == right_tree);
}

TEST(equalityOperator, returnTrueForIdenticalTrees)
{
    general_tree<int> left_tree;
    auto root1 = left_tree.create_root(100);
    auto child1 = left_tree.insert_left_child(root1, 200);
    auto child2 = left_tree.insert_right_sibling(child1, 300);
    left_tree.insert_left_child(child1, 400);

    general_tree<int> right_tree;
    auto root2 = right_tree.create_root(100);
    auto child3 = right_tree.insert_left_child(root2, 200);
    auto child4 = right_tree.insert_right_sibling(child3, 300);
    right_tree.insert_left_child(child3, 400);

    EXPECT_TRUE(left_tree == right_tree);
}
