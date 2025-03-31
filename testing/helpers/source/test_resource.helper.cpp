#include "test_resource.helper.h"
#include <cassert>

thread_local unsigned test_resource::instances_created = 0;
thread_local unsigned test_resource::move_constructor_calls = 0;
thread_local unsigned test_resource::destructor_calls = 0;
thread_local unsigned test_resource::copy_constructor_calls = 0;

void test_resource::reset_calls_count() noexcept
{
	instances_created = 0;
	copy_constructor_calls = 0;
	move_constructor_calls = 0;
	destructor_calls = 0;
}

std::size_t test_resource::populate_tree_resource(general_tree<test_resource>& test_resource)
{
	assert(test_resource.empty());

	test_resource.emplace_root("10", 10);
	auto n20 = test_resource.emplace_left_child(test_resource.root(), "20", 20);
	auto n30 = test_resource.emplace_left_child(test_resource.root(), "30", 30);
	auto n40 = test_resource.emplace_left_child(test_resource.root(), "40", 40);

	auto n201 = test_resource.emplace_left_child(n20, "201", 201);
	auto n202 = test_resource.emplace_left_child(n20, "202", 202);
	test_resource.emplace_left_child(n201, "2011", 2011);
	test_resource.emplace_left_child(n201, "2012", 2012);

	auto n301 = test_resource.emplace_left_child(n30, "301", 301);
	auto n302 = test_resource.emplace_left_child(n30, "302", 302);
	test_resource.emplace_left_child(n302, "3021", 3021);
	test_resource.emplace_left_child(n302, "3022", 3022);

	auto n401 = test_resource.emplace_left_child(n40, "401", 401);
	auto n402 = test_resource.emplace_left_child(n40, "402", 402);
	test_resource.emplace_left_child(n401, "4011", 4011);
	test_resource.emplace_left_child(n401, "4012", 4012);

	std::size_t size = test_resource.root().descendants_count() + 1;
	return size;
}