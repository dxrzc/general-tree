#include <gtest/gtest.h>
#include "general_tree.h"

TEST(emplace_right_sibling, throwInvalidArgumentIfDestinyNodeIsNull)
{
	general_tree<int> empty_tree;
	general_tree<int>::node null_node = empty_tree.root();
	EXPECT_THROW(empty_tree.emplace_right_sibling(null_node, 1), std::invalid_argument);
}

TEST(emplace_right_sibling, returnNodePointingToRootOfTheInsertedTree)
{
	general_tree<int> tree(1);
	general_tree<int>::node destiny = tree.insert_left_child(tree.root(), 2);

	general_tree<int>::node inserted = tree.emplace_right_sibling(destiny, 7842342);
	
	EXPECT_EQ(destiny.right_sibling(), inserted);
}

TEST(emplace_right_sibling, parentOfTheNewNodeShouldBeTheParentOfTheDestinyNode)
{
	general_tree<int> tree(1);
	general_tree<int>::node destiny = tree.insert_left_child(tree.root(), 2);
	general_tree<int>::node inserted = tree.emplace_right_sibling(destiny, 3);
	EXPECT_EQ(inserted.parent(), destiny.parent());
}

TEST(emplace_right_sibling, leftChildOfTheNewNodeShouldBeNull)
{
	general_tree<int> tree(1);
	general_tree<int>::node destiny = tree.insert_left_child(tree.root(), 2);
	general_tree<int>::node inserted = tree.emplace_right_sibling(destiny, 3);
	EXPECT_TRUE(inserted.left_child().is_null());
}

TEST(emplace_right_sibling, ifThereWasNotAPreviousRightSiblingTheRightSiblingOfNewNodeShouldBeNull)
{
	general_tree<int> tree(1);
	general_tree<int>::node destiny = tree.insert_left_child(tree.root(), 2);
	general_tree<int>::node inserted = tree.emplace_right_sibling(destiny, 3);
	EXPECT_TRUE(inserted.right_sibling().is_null());
}

TEST(emplace_right_sibling, previousRightSiblingShouldBeTheRightSiblingOfTheNewNode)
{
	general_tree<int> tree(1);
	general_tree<int>::node destiny = tree.insert_left_child(tree.root(), 2);

	general_tree<int>::node previous_right_sibling = tree.emplace_right_sibling(destiny, 3);
	general_tree<int>::node new_right_sibling = tree.emplace_right_sibling(destiny, 4);

	EXPECT_EQ(new_right_sibling.right_sibling(), previous_right_sibling);
}

TEST(emplace_right_sibling, multipleInsertionsDoNotCauseErrors)
{
	general_tree<int> tree(100);
	general_tree<int>::node destiny = tree.insert_left_child(tree.root(), 101);

	EXPECT_NO_FATAL_FAILURE({
		const unsigned count = 10;
		for (unsigned i = 0; i < count; i++)
			tree.emplace_right_sibling(destiny, i);
		EXPECT_EQ(tree.root().children_count(), count + 1);
	});
}