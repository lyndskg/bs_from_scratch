# Set the minimum CMake version required
cmake_minimum_required(VERSION 3.25)

# Set your project name and C++ standard
project(Test CXX)
set(CMAKE_CXX_STANDARD 20)

# Download and include Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)

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
    target_include_directories(${obj_name}.o PRIVATE ${googletest_SOURCE_DIR}/googletest/include)
    target_link_libraries(${obj_name}.o PRIVATE gtest gtest_main)
    target_compile_definitions(${obj_name}.o PRIVATE USE_GTEST)
endforeach()

# Combine all test objects into a single test executable
add_executable(testProgram ${TESTOBJS} ${SRCS})

# Set the arm64 architecture as the target
set(CMAKE_OSX_ARCHITECTURES "arm64")

# Specify the output directory for the test executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Optionally, you can define your own ASSERT_TRUE macro
# Uncomment the following line if you want to define your own ASSERT_TRUE macro
# target_compile_definitions(runUnitTests PRIVATE ASSERT_TRUE(expr) if (!(expr)) { GTEST_FATAL_FAILURE_("Assertion failed: ") expr)

# Register the test with CTest
add_test(NAME default_ctor COMMAND testProgram)
