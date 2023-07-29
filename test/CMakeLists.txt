# Set the minimum macOS version required
cmake_minimum_required(VERSION 3.25)

# Set your project name and C++ standard
project(Test CXX)
set(CMAKE_CXX_STANDARD 20)

# Define the source files used in the main project
set(SRCS
        main.cpp
        src/Program.cpp
        src/inputReader.cpp
        src/blackScholesModel.cpp
        )

# Create object file names from source file names
set(OBJS)
foreach(src ${SRCS})
    get_filename_component(obj_name ${src} NAME_WE)
    list(APPEND OBJS ${CMAKE_BINARY_DIR}/${obj_name}.o)
endforeach()

# Compile rule for each .cpp file to produce .o files
foreach(src ${SRCS})
    get_filename_component(obj_name ${src} NAME_WE)
    add_compile_options("-arch" "arm64")
    add_executable(${obj_name}.o ${src})
endforeach()

# Link rule to produce the final executable
add_executable(bs ${OBJS})
target_link_options(bs PRIVATE "-arch" "arm64")

# Add include directories if needed
target_include_directories(bs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/customMake)

# Set additional compiler flags
target_compile_options(bs PRIVATE
        "-Wconversion"
        "-Wall"
        "-Werror"
        "-Wextra"
        "-pedantic"
        )

# Set the arm64 architecture as the target
set(CMAKE_OSX_ARCHITECTURES "arm64")

# Specify the output directory for the final executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add any other libraries or link options here (if needed)
# ...

# Enable CTest for testing
include(CTest)
enable_testing()

# Define the source files used in the test programs
set(TESTSRCS
        gtest.cpp
        test/testProgram.cpp
        test/testInputReader.cpp
        test/testBlackScholesModel.cpp
        )

# Create object file names from test source file names
set(TESTOBJS)
foreach(src ${TESTSRCS})
    get_filename_component(obj_name ${src} NAME_WE)
    list(APPEND TESTOBJS ${CMAKE_BINARY_DIR}/${obj_name}.o)
endforeach()

# Compile rule for each test .cpp file to produce .o files
foreach(src ${TESTSRCS})
    get_filename_component(obj_name ${src} NAME_WE)
    add_compile_options("-arch" "arm64")
    add_executable(${obj_name}.o ${src})
endforeach()


# Download and include Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)


# Link rule to produce the test executable(s)
add_executable(testProgram ${TESTOBJS} ${OBJS})
target_link_options(testProgram PRIVATE "-arch" "arm64")
target_link_libraries(testProgram PRIVATE gtest gtest_main)

# Define ASSERT_TRUE macro if using Google Test
target_compile_definitions(testProgram PRIVATE USE_GTEST)

# Register the test with CTest
add_test(NAME MyTests COMMAND testProgram)

# Add the test target executable(s)
add_executable(testProgram ${TEST_SOURCES})

# Add include directories if needed
target_include_directories(testProgram PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ../include/customMake)

# Link the test executable with gtest and your source code
target_link_libraries(testProgram PRIVATE gtest gtest_main src/Program.cpp)

# Define ASSERT_TRUE macro if using Google Test
target_compile_definitions(testProgram PRIVATE USE_GTEST)

# Register the test with CTest
add_test(NAME MyTests COMMAND testProgram)

# Optionally, you can define your own ASSERT_TRUE macro
# Uncomment the following line if you want to define your own ASSERT_TRUE macro
# target_compile_definitions(runUnitTests PRIVATE ASSERT_TRUE(expr) if (!(expr)) { GTEST_FATAL_FAILURE_("Assertion failed: ") expr)

#
#add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
#
##set(test_SRCS ADD ALL TEST SOURCE FILES HERE)
#add_executable(runUnitTests gtest.cpp testProgram.cpp)
#target_link_libraries(runUnitTests gtest gmock core)
##add_test(runUnitTests runUnitTests) #included in all tutorials but I don't know what it actually does.
#
## Set the output extension for C++ object files
#set(CMAKE_CXX_OUTPUT_EXTENSION .o)
#
## Add your main executable sources to the target (e.g., "test" in this case)
#add_executable(test testProgram.cpp)
#
#
## Set the C++ standard library to libc++ (for macOS)
#if (APPLE)
#    target_link_options(test PRIVATE -stdlib=libc++)
#endif()
#
### Link the main executable with any necessary libraries
##target_link_libraries(bs PRIVATE libstdc++)
### include libcurl eventually
#
## Set the C++ standard for the main executable
#target_compile_features(test PRIVATE cxx_std_20)
#
## Find and include Google Test
#find_package(GTest REQUIRED)
#
## Link the test executable against the Google Test library
#target_link_libraries(test PRIVATE GTest::GTest GTest::Main gtest_main)
#
## Define ASSERT_TRUE macro if using Google Test
#target_compile_definitions(test PRIVATE USE_GTEST)
#
#add_test(NAME example_test COMMAND example)
#
### Optionally, you can define your own ASSERT_TRUE macro
### Uncomment the following line if you want to define your own ASSERT_TRUE macro
##target_compile_definitions(test_bs PRIVATE ASSERT_TRUE(expr) if (!(expr)) { GTEST_FATAL_FAILURE_("Assertion failed: ") expr)
#
#add_test(NAME default_ctor COMMAND test)
#add_test(NAME custom_ctor COMMAND test)
#
## List all your test source files here
#set(TEST_SOURCES
#        testProgram.cpp
#        testInputReader.cpp
#        testBlackScholesModel.cpp
#        # Add more test files as needed
#        )
#
## Add the test target executable(s)
#add_executable(test ${TEST_SOURCES})
#
## Add include directories if needed
#target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ../include/customMake)
#
## Link the test executable with gtest and your source code
#target_link_libraries(test PRIVATE gtest gtest_main)
#
## Add custom target for running tests
#add_custom_target(run_tests COMMAND test)
#
## Register the test with CTest
#add_test(NAME MyTests COMMAND test)
##add_test(NAME MyTests2 COMMAND test)
