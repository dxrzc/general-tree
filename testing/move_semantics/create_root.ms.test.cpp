#include <gtest/gtest.h>
#include "general-tree.h"
#include "move_semantics.fixture.h"

TEST_F(move_semantics_fixture, create_root_ByCopy)
{
	general_tree<test_resource> tree;
	test_resource resource ("", 0);

	tree.create_root(resource);

	EXPECT_EQ(test_resource::copy_constructor_calls, 1);
	EXPECT_EQ(test_resource::move_constructor_calls, 0);
	EXPECT_EQ(test_resource::instances_created, 2);
}

TEST_F(move_semantics_fixture, create_root_ByMov)
{
	general_tree<test_resource> tree;
	test_resource resource("", 0);

	tree.create_root(std::move(resource));

	EXPECT_EQ(test_resource::copy_constructor_calls, 0);
	EXPECT_EQ(test_resource::move_constructor_calls, 1);
	EXPECT_EQ(test_resource::instances_created, 1);
}