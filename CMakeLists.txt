cmake_minimum_required(VERSION 3.5)

project(general_tree_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE TEST_SOURCES "testing/*.cpp")

add_executable(general_tree_test ${TEST_SOURCES})

target_include_directories(
	general_tree_test
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

target_link_libraries(
  general_tree_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(general_tree_test)