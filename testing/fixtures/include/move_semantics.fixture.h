#pragma once
#include <gtest/gtest.h>

class test_resource
{
private:
	std::string m_string;
	int m_int;

public:
	static thread_local unsigned instances_created;
	static thread_local unsigned copy_constructor_calls;
	static thread_local unsigned move_constructor_calls;
	static thread_local unsigned destructor_calls;

	// this function does not resets destructor_calls!!
	static void reset_calls_count() noexcept
	{
		instances_created = 0;
		copy_constructor_calls = 0;
		move_constructor_calls = 0;		
	}	

	test_resource() = delete;

	test_resource(const std::string& string, int integer)
		: m_string(string), m_int(integer)
	{
		++instances_created;
	}

	test_resource(const test_resource& rhs)
		: m_string(rhs.m_string), m_int(rhs.m_int)
	{
		++copy_constructor_calls;
		++instances_created;
	}

	test_resource(test_resource&& rhs) noexcept
		: m_string(std::move(rhs.m_string)), m_int(rhs.m_int)
	{
		++move_constructor_calls;
	}

	~test_resource() { ++destructor_calls; }
};

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