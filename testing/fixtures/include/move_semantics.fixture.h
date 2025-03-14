#pragma once
#include <gtest/gtest.h>
#include "test_resource.helper.h"

class move_semantics_fixture : public testing::Test
{
	void SetUp() override
	{
		test_resource::instances_created = 0;
		test_resource::copy_constructor_calls = 0;
		test_resource::move_constructor_calls = 0;
		test_resource::destructor_calls = 0;
	}
};