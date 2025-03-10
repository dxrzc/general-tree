#include <gtest/gtest.h>
#include "general-tree.h"

TEST(insert_right_sibling, throwInvalidArgumentExceptionIfDestinyIsNull)
{
	general_tree<int> tree(1);
	general_tree<int>::node left_child = tree.insert_left_child(tree.root(), 2);
	general_tree<int>::node null_destiny = left_child.left_child();

	// insert a new tree as right sibling to the null node
	general_tree<int> new_tree(3);
	EXPECT_THROW(tree.insert_right_sibling(null_destiny, new_tree), std::invalid_argument);
}

TEST(insert_right_sibling, throwInvalidArgumentExceptionIfDestinyIsARoot)
{
	general_tree<int> tree(1);
	general_tree<int>::node root_destiny = tree.root();

	// insert the new tree as right sibling to the root
	general_tree<int> new_tree(2);
	EXPECT_THROW(tree.insert_right_sibling(root_destiny, new_tree), std::invalid_argument);
}

TEST(insert_right_sibling, returnNodePointingToTheNewInsertedTreeRoot)
{
	general_tree<int> tree(100);
	general_tree<int>::node destiny_node = tree.insert_left_child(tree.root(), 200);

	// new tree to insert
	const int new_tree_root_value = 2025;
	general_tree<int> new_tree(new_tree_root_value);

	// returned node should contain the same data as the new tree root
	general_tree<int>::node right_sibling_node = tree.insert_right_sibling(destiny_node, new_tree);
	EXPECT_EQ(tree.data(right_sibling_node), new_tree_root_value);
}

TEST(insert_right_sibling, throwInvalidArgumentIfTreeIsInsertedToItself)
{
	EXPECT_TRUE(true);
}

TEST(insert_right_sibling, destinyNodeDoesNotSufferChangesIfEmptyTreeIsInserted)
{
	general_tree<int> tree(100);
	general_tree<int>::node destiny_node = tree.insert_left_child(tree.root(), 200);

	// inserting an empty tree
	general_tree<int> empty_tree;
	tree.insert_right_sibling(destiny_node, empty_tree);

	// destiny should not have suffered changes
	EXPECT_TRUE(destiny_node.right_sibling().is_null());
	EXPECT_TRUE(destiny_node.left_child().is_null());
	EXPECT_EQ(destiny_node.parent(), tree.root());
}

TEST(insert_right_sibling, returnNullNodeIfInsertedTreeIsEmpty)
{
	general_tree<int> tree(100);
	general_tree<int>::node destiny_node = tree.insert_left_child(tree.root(), 200);

	// inserting an empty tree
	general_tree<int> empty_tree;
	general_tree<int>::node inserted = tree.insert_right_sibling(destiny_node, empty_tree);

	EXPECT_TRUE(inserted.is_null());
}

TEST(insert_right_sibling, newTreeRemainsAsNull)
{
	general_tree<int> tree(100);
	general_tree<int>::node destiny_node = tree.insert_left_child(tree.root(), 200);

	// new tree to insert
	general_tree<int> new_tree(1313);
	new_tree.insert_left_child(new_tree.root(), 1314);

	// insert new tree to destiny node
	tree.insert_left_child(destiny_node, new_tree);

	// new tree should remain empty
	EXPECT_TRUE(new_tree.empty());
}

TEST(insert_right_sibling, insertedTreeRootShouldBeTheRightSiblingOfTheDestinyNode)
{
	general_tree<int> tree(100);
	general_tree<int>::node destiny_node = tree.insert_left_child(tree.root(), 200);

	// insert a new tree as right sibling to the destiny node
	general_tree<int> new_tree(1313);
	general_tree<int>::node inserted_right_sibling = tree.insert_right_sibling(destiny_node, new_tree);

	// destiny's right sibling should be the inserted tree
	EXPECT_EQ(destiny_node.right_sibling(), inserted_right_sibling);
}

TEST(insert_right_sibling, previousRightSiblingShouldBeTheRightSiblingOfTheNewTreeRoot)
{
	general_tree<int> tree(100);
	general_tree<int>::node destiny_node = tree.insert_left_child(tree.root(), 200);

	// inserting a right sibling
	general_tree<int> right_sibling_tree(1313);
	general_tree<int>::node previous_right_sibling = tree.insert_right_sibling(destiny_node, right_sibling_tree);

	// inserting a new tree
	general_tree<int> new_tree(1314);
	general_tree<int>::node new_tree_root = new_tree.insert_right_sibling(destiny_node, new_tree);

	// previous right sibling is the right sibling of the new tree root
	EXPECT_EQ(new_tree_root.right_sibling(), previous_right_sibling);
}

TEST(insert_right_sibling, increaseTheParentsChildCount)
{
	general_tree<int> tree(100);
	general_tree<int>::node destiny_node = tree.insert_left_child(tree.root(), 200);
	std::size_t tree_child_count = tree.children_count(tree.root());

	// inserting a new tree as right sibling
	general_tree<int> new_tree(1313);
	tree.insert_right_sibling(destiny_node, new_tree);

	// parent's child count should have increased
	EXPECT_EQ(tree.children_count(tree.root()), tree_child_count + 1);
}

TEST(insert_right_sibling, multipleInsertionsDoNotCauseErrors)
{
	general_tree<int> tree(100);
	general_tree<int>::node destiny_node = tree.insert_left_child(tree.root(), 200);

	EXPECT_NO_FATAL_FAILURE({
		const unsigned children_count = 10;

		for (unsigned i = 0; i < children_count; i++)
		{
			general_tree<int> new_tree(i);
			tree.insert_right_sibling(destiny_node, new_tree);
		}

		EXPECT_EQ(tree.children_count(tree.root()), children_count + 1);
	});
}