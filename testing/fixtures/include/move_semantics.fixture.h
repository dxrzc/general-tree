#pragma once
#include <gtest/gtest.h>
#include "test_resource.helper.h"

class move_semantics_fixture : public testing::Test
{
	void SetUp() override
	{
		test_resource::reset_calls_count();
	}
};