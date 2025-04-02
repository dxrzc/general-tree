#include <gtest/gtest.h>
#include "general_tree.h"

TEST(class_node, throwInvalidArgumentIfNodeIsNull)
{
    general_tree<int> tree;
    general_tree<int>::node null_node = tree.root();

    // Using a block to avoid the "nodiscard warning"
    EXPECT_THROW({
        auto ignored = null_node.depth();
    }, std::invalid_argument);
}

TEST(class_node, depth_returnZeroIfNodeIsRoot)
{
    general_tree<int> tree(1);
    EXPECT_EQ(tree.root().depth(), 0);
}

TEST(class_node, depth_returnOneForChildOfRoot)
{
    general_tree<int> tree(1);
    auto child = tree.insert_left_child(tree.root(), 2);
    EXPECT_EQ(child.depth(), 1);
}

TEST(class_node, depth_returnTwoForGrandchildOfRoot)
{
    general_tree<int> tree(1);
    auto child = tree.insert_left_child(tree.root(), 2);
    auto grandchild = tree.insert_left_child(child, 3);
    EXPECT_EQ(grandchild.depth(), 2);
}

TEST(class_node, depth_returnCorrectDepthForSiblingNodes)
{
    general_tree<int> tree(1);
    auto child = tree.insert_left_child(tree.root(), 2);
    auto sibling = tree.insert_right_sibling(child, 3);

    EXPECT_EQ(child.depth(), 1);
    EXPECT_EQ(sibling.depth(), 1);
}

TEST(class_node, depth_returnCorrectDepthForDeepHierarchy)
{
    general_tree<int> tree(1);
    auto child1 = tree.insert_left_child(tree.root(), 2);
    auto child2 = tree.insert_left_child(child1, 3);
    auto child3 = tree.insert_left_child(child2, 4);

    EXPECT_EQ(child1.depth(), 1);
    EXPECT_EQ(child2.depth(), 2);
    EXPECT_EQ(child3.depth(), 3);
}

TEST(class_node, depth_returnCorrectDepthWithMultipleBranches)
{
    general_tree<int> tree(1);
    auto child1 = tree.insert_left_child(tree.root(), 2);
    auto child2 = tree.insert_right_sibling(child1, 3);
    auto grandchild1 = tree.insert_left_child(child1, 4);
    auto grandchild2 = tree.insert_left_child(child2, 5);

    EXPECT_EQ(child1.depth(), 1);
    EXPECT_EQ(child2.depth(), 1);
    EXPECT_EQ(grandchild1.depth(), 2);
    EXPECT_EQ(grandchild2.depth(), 2);
}

TEST(class_node, depth_returnCorrectDepthForComplexTree)
{
    general_tree<int> tree(1);
    auto a = tree.insert_left_child(tree.root(), 2);
    auto b = tree.insert_right_sibling(a, 3);
    auto c = tree.insert_left_child(a, 4);
    auto d = tree.insert_left_child(b, 5);
    auto e = tree.insert_right_sibling(d, 6);
    auto f = tree.insert_left_child(d, 7);

    EXPECT_EQ(a.depth(), 1);
    EXPECT_EQ(b.depth(), 1);
    EXPECT_EQ(c.depth(), 2);
    EXPECT_EQ(d.depth(), 2);
    EXPECT_EQ(e.depth(), 2);
    EXPECT_EQ(f.depth(), 3);
}
