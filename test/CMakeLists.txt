# Set the minimum macOS version required
cmake_minimum_required(VERSION 3.25)


# List all your test source files here
set(TEST_SOURCES
        testProgram.cpp
        testInputReader.cpp
        testBlackScholesModel.cpp
        # Add more test files as needed
        )

# Add the test executable target
add_executable(test ${TEST_SOURCES})

# Link the test executable with gtest and your source code
target_link_libraries(test PRIVATE gtest gtest_main)

# Add include directories if needed
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Register the test with CTest
add_test(NAME MyTests COMMAND test)
#add_test(NAME MyTests2 COMMAND test)
