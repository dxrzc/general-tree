#include "test_resource.helper.h"

thread_local unsigned test_resource::instances_created = 0;
thread_local unsigned test_resource::move_constructor_calls = 0;
thread_local unsigned test_resource::destructor_calls = 0;
thread_local unsigned test_resource::copy_constructor_calls = 0;