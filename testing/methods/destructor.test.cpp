#include <gtest/gtest.h>
#include "test_resource.helper.h"

class destructor : public ::testing::Test
{
	void SetUp() override
	{
		test_resource::reset_calls_count();
	}
};

TEST_F(destructor, emptyTreeDoesNotCauseFatalFailure)
{
	EXPECT_NO_FATAL_FAILURE({
		general_tree<int> test_tree;
	});
}

TEST_F(destructor, treeContainsOnlyRoot)
{
	{
		general_tree<test_resource> test_tree;
		test_tree.emplace_root("root", 1);
	}
	EXPECT_EQ(test_resource::destructor_calls, 1);
}

TEST_F(destructor, deleteAllNodes)
{
	{
		general_tree<test_resource> test_tree;
		auto root = test_tree.emplace_root("root", 1);
		auto child1 = test_tree.emplace_left_child(root, "child1", 2);
		auto child2 = test_tree.emplace_left_child(root, "child2", 3);
        test_tree.emplace_left_child(child1, "child3", 4);
        test_tree.emplace_left_child(child2, "child4", 5);
	}
	EXPECT_EQ(test_resource::destructor_calls, 5);
}
