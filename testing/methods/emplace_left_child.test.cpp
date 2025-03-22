#include <gtest/gtest.h>
#include "general-tree.h"

TEST(emplace_left_child, throwInvalidArgumentIfDestinyNodeIsNull)
{
	general_tree<int> empty_tree;
	general_tree<int>::node null_node = empty_tree.root();

	EXPECT_THROW(empty_tree.emplace_left_child(null_node, 1), std::invalid_argument);
}

TEST(emplace_left_child, returnNodePointingToRootOfTheInsertedTree)
{
	general_tree<int> tree(1);
	general_tree<int>::node inserted = tree.emplace_left_child(tree.root(), 7842342);

	EXPECT_EQ(inserted, tree.root().left_child());
}

TEST(emplace_left_child, parentOfTheInsertedNodeShouldBeTheNodePassedAsArgument)
{
	general_tree<int> tree(1);
	general_tree<int>::node inserted = tree.emplace_left_child(tree.root(), 7842342);

	EXPECT_EQ(inserted.parent(), tree.root());
}

TEST(emplace_left_child, leftChildOfTheInsertedNodeShouldBeNull)
{
	general_tree<int> tree(1);
	general_tree<int>::node inserted = tree.emplace_left_child(tree.root(), 7842342);
	EXPECT_TRUE(inserted.left_child().is_null());
}

TEST(emplace_left_child, ifThereWasNotAPreviousLeftChildRightSiblingOfNewNodeShouldBeNull)
{
	general_tree<int> tree(1);
	general_tree<int>::node inserted = tree.emplace_left_child(tree.root(), 7842342);
	EXPECT_TRUE(inserted.right_sibling().is_null());
}

TEST(emplace_left_child, previousLeftChildShouldBeTheRightSiblingOfTheNewNode)
{
	general_tree<int> tree(1);
	general_tree<int>::node destiny_node = tree.root();
	general_tree<int>::node previous_left_child = tree.insert_left_child(destiny_node, 2);

	general_tree<int>::node new_left_child = tree.emplace_left_child(tree.root(), 3);

	EXPECT_EQ(new_left_child.right_sibling(), previous_left_child);
}

TEST(emplace_left_child, multipleInsertionsDoNotCauseErrors)
{
	general_tree<int> tree(100);

	EXPECT_NO_FATAL_FAILURE({
		const unsigned count = 10;
		for (unsigned i = 0; i < count; i++)		
			tree.emplace_left_child(tree.root(), i);		

		EXPECT_EQ(tree.root().children_count(), count);
	});
}