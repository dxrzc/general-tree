#include <gtest/gtest.h>
#include "general-tree.h"
#include "move_semantics.fixture.h"

TEST_F(move_semantics_fixture, emplace_left_child)
{
	general_tree<test_resource> tree;
	tree.create_root(test_resource("", 0));
	test_resource::reset_calls_count();

	tree.emplace_left_child(tree.root(), "", 1);	
	
	EXPECT_FALSE(tree.root().left_child().is_null());
	EXPECT_EQ(test_resource::instances_created, 1);
	EXPECT_EQ(test_resource::copy_constructor_calls, 0);
	EXPECT_EQ(test_resource::move_constructor_calls, 0);
}

TEST_F(move_semantics_fixture, emplace_left_child_SendTheFullObjectShouldAlsoWork)
{
	general_tree<test_resource> tree;
	tree.create_root(test_resource("", 0));
	test_resource::reset_calls_count();

	test_resource resource("", 1);
	tree.emplace_left_child(tree.root(), std::move(resource));

	EXPECT_EQ(test_resource::instances_created, 1);
	EXPECT_EQ(test_resource::copy_constructor_calls, 0);
	EXPECT_EQ(test_resource::move_constructor_calls, 1);
}