#include <gtest/gtest.h>
#include "general-tree.h"
#include "move_semantics.fixture.h"

TEST_F(move_semantics_fixture, constructor_ByCopy)
{
	test_resource resource("", 0);
	general_tree<test_resource> tree(resource);

	EXPECT_EQ(test_resource::instances_created, 2);
	EXPECT_EQ(test_resource::copy_constructor_calls, 1);
	EXPECT_EQ(test_resource::move_constructor_calls, 0);
}

TEST_F(move_semantics_fixture, constructor_ByMov)
{
	test_resource resource("", 0);
	general_tree<test_resource> tree(std::move(resource));

	EXPECT_EQ(test_resource::instances_created, 1);
	EXPECT_EQ(test_resource::copy_constructor_calls, 0);
	EXPECT_EQ(test_resource::move_constructor_calls, 1);
}