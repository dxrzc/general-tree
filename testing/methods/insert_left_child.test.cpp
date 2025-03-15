#include <gtest/gtest.h>
#include "general-tree.h"

TEST(insert_left_child, throwInvalidArgumentExceptionIfDestinyIsNull)
{
	general_tree<int> tree;
	general_tree<int>::node null_node = tree.root();

	// insert a new tree as left child to the null node
	general_tree<int> new_tree(1);
	EXPECT_THROW(tree.insert_left_child(null_node, new_tree), std::invalid_argument);
}

TEST(insert_left_child, returnNodePointingToRootOfTheInsertedTree)
{
	general_tree<int> tree(1);
	const int new_tree_root_value = 2;
	general_tree<int> new_tree(new_tree_root_value);

	general_tree<int>::node inserted = tree.insert_left_child(tree.root(), new_tree);

	EXPECT_EQ(tree.data(inserted), new_tree_root_value);
}

TEST(insert_left_child, destinyNodeDoesNotSufferChangesIfEmptyTreeIsInserted)
{
	general_tree<int> tree(1);
	general_tree<int>::node destiny_node = tree.root();
	
	// insert an empty tree as left child to the destiny node
	general_tree<int> empty_tree;	
	tree.insert_left_child(destiny_node, empty_tree);

	EXPECT_TRUE(destiny_node.left_child().is_null());
	EXPECT_TRUE(destiny_node.right_sibling().is_null());
	EXPECT_TRUE(destiny_node.is_root());
}	

TEST(insert_left_child, returnNullNodeIfInsertedTreeIsEmpty)
{
	general_tree<int> destiny(1);
	general_tree<int> new_tree;

	general_tree<int>::node inserted_node = destiny.insert_left_child(destiny.root(), new_tree);
	EXPECT_TRUE(inserted_node.is_null());
}

TEST(insert_left_child, newTreeRemainsAsNull)
{
	general_tree<int> destiny(1);
	general_tree<int> new_tree;

	destiny.insert_left_child(destiny.root(), new_tree);

	EXPECT_TRUE(new_tree.empty());
}

TEST(insert_left_child, insertedTreeRootShouldBeTheLeftChildOfTheDestinyNode)
{
	general_tree<int> tree(1);
	general_tree<int>::node destiny_node = tree.root();

	// insert a new tree as left child to the destiny node
	general_tree<int> new_tree(2);
	general_tree<int>::node inserted = tree.insert_left_child(destiny_node, new_tree);

	EXPECT_EQ(destiny_node.left_child(), inserted);
}

TEST(insert_left_child, previousLeftChildShouldBeTheRightSiblingOfTheNewNode)
{
	general_tree<int> tree(1);
	general_tree<int>::node destiny_node = tree.root();

	// insert a left child
	general_tree<int>::node previous_left_child = tree.insert_left_child(destiny_node, 2);

	// insert a new left child
	general_tree<int> new_tree(3);
	general_tree<int>::node new_tree_root = new_tree.insert_left_child(destiny_node, 4);

	EXPECT_EQ(new_tree_root.right_sibling(), previous_left_child);
}

TEST(insert_left_child, nodesInsertedShouldIncreaseTheHeightCount)
{
	general_tree<int> tree(1);
	tree.insert_left_child(tree.root(), 2);
	std::size_t tree_previous_height = tree.height(tree.root());

	// create a new tree and populate it
	general_tree<int> new_tree(3);
	new_tree.insert_left_child(new_tree.root(), 4);
	new_tree.insert_left_child(new_tree.root().left_child(), 5);
	new_tree.insert_left_child(new_tree.root().left_child().left_child(), 6);
	std::size_t new_tree_height = tree.height(new_tree.root());

	tree.insert_left_child(tree.root(), new_tree);
	std::size_t tree_updated_height = tree.height(tree.root());

	EXPECT_EQ(tree_updated_height, tree_previous_height + new_tree_height);
}

TEST(insert_left_child, throwInvalidArgumentIfTreeisInsertedToItself)
{
	general_tree<int> destiny(1);
	// try to insert a tree as its own left child
	EXPECT_THROW(destiny.insert_left_child(destiny.root(), destiny), std::invalid_argument);
}

TEST(insert_left_child, multipleInsertionsDoNotCauseErrors)
{
	general_tree<int> tree(100);

	EXPECT_NO_FATAL_FAILURE({
		const unsigned count = 10;
		for(unsigned i = 0; i < count; i++)
		{
			general_tree<int> new_tree(i);
			tree.insert_left_child(tree.root(), new_tree);
		}

		EXPECT_EQ(tree.children_count(tree.root()), count);
	});
}