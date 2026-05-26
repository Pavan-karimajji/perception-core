cmake_minimum_required(VERSION 3.22)

# Try to find GTest in system or package manager first
find_package(GTest QUIET)

if(NOT GTest_FOUND)
    message(STATUS "GTest not found locally. Fetching GoogleTest from GitHub...")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    # Prevent overriding the compiler/linker settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

# Define test executable
add_executable(perception_core_tests
    unit/test_detector.cpp
    unit/test_tracker.cpp
)

# Link against library and gtest
target_link_libraries(perception_core_tests PRIVATE
    perception_core
    GTest::gtest_main
)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(perception_core_tests)
