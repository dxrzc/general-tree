#include <gtest/gtest.h>
#include "general-tree.h"
#include "move_semantics.fixture.h"

TEST_F(move_semantics_fixture, insert_left_child_ByCopy)
{
	general_tree<test_resource> tree;	
	tree.create_root(test_resource("", 0)); 

	test_resource::reset_calls_count();

	test_resource resource("", 1);
	tree.insert_left_child(tree.root(), resource);

	EXPECT_EQ(test_resource::copy_constructor_calls, 1);
	EXPECT_EQ(test_resource::move_constructor_calls, 0);
	EXPECT_EQ(test_resource::instances_created, 2);
}

TEST_F(move_semantics_fixture, insert_left_child_ByMov)
{
	general_tree<test_resource> tree;
	tree.create_root(test_resource("", 0));

	test_resource::reset_calls_count();

	test_resource resource("", 1);
	tree.insert_left_child(tree.root(), std::move(resource));

	EXPECT_EQ(test_resource::copy_constructor_calls, 0);
	EXPECT_EQ(test_resource::move_constructor_calls, 1);
	EXPECT_EQ(test_resource::instances_created, 1);
}