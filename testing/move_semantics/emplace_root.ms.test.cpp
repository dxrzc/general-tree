#include <gtest/gtest.h>
#include "move_semantics.fixture.h"

TEST_F(move_semantics_fixture, emplace_root)
{
	general_tree<test_resource> tree;

	tree.emplace_root("", 0);

	EXPECT_FALSE(tree.root().is_null());

	EXPECT_EQ(test_resource::instances_created, 1);
	EXPECT_EQ(test_resource::copy_constructor_calls, 0);
	EXPECT_EQ(test_resource::move_constructor_calls, 0);
}

TEST_F(move_semantics_fixture, emplace_root_SendTheFullObjectShouldAlsoWork)
{
	general_tree<test_resource> tree;
	test_resource resource("", 0);

	tree.emplace_root(std::move(resource));

	EXPECT_EQ(test_resource::instances_created, 1);
	EXPECT_EQ(test_resource::copy_constructor_calls, 0);
	EXPECT_EQ(test_resource::move_constructor_calls, 1);
}