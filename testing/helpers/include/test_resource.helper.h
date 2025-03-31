#pragma once

#include <string>
#pragma once
#include "general-tree.h"

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
	static void reset_calls_count() noexcept;

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

	static std::size_t populate_tree_resource(general_tree<test_resource>& test_resource);

	~test_resource() { ++destructor_calls; }
};