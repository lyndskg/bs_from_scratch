# Set the minimum macOS version required
cmake_minimum_required(VERSION 3.25)

# Set your project's executable name, language, and C++ standard
project(schlisselTest CXX)
set(CMAKE_CXX_STANDARD 20)

# Set the output extension for C++ object files
set(CMAKE_CXX_OUTPUT_EXTENSION ".o")

# Set additional compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion -Wall -Werror -Wextra -pedantic")

# Set the arm64 architecture as the target
set(CMAKE_OSX_ARCHITECTURES arm64)

# Add your test files here
set(TEST_SOURCES tests/testProgram.cpp)

# Define and add the test executable to the target (e.g., "schlissel" in this case)
# and link it with the test source file(s)
# Add your custom test framework and test cases to the test executable
add_executable(schlissel ${TEST_SOURCES} schlissel.h)

# Set the C++ standard for the test executable
target_compile_features(schlissel PRIVATE cxx_std_20)
#
# Set additional compiler flags for the target
target_compile_options(schlissel PRIVATE -g3 -DDEBUG)

# Link the test executable with any necessary libraries
# (Note: You can remove this line if your custom test framework does not require this library)
target_link_libraries(schlissel PRIVATE libstdc++)

# Add a test that runs your custom test framework
add_test(NAME allTests COMMAND schlissel)

# Enable the 'test' target to run all tests with 'make test' (optional)
enable_testing()

# Set a single timeout value for all test cases in the "schlissel" suite
set_tests_properties(schlissel PROPERTIES TIMEOUT 10)


## Add your custom test framework's include directories and any other dependencies
#target_include_directories(MyCustomTestRunner PRIVATE path/to/custom_test_framework)
#target_link_libraries(MyCustomTestRunner PRIVATE path/to/custom_test_framework_lib)


## Create a test suite target and group all individual test cases under it
#add_test(NAME MyTestSuite COMMAND ${CMAKE_CTEST_COMMAND} --force-new-ctest-process --test-suite MyTestSuite)


