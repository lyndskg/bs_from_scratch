# Set the minimum CMake version required
cmake_minimum_required(VERSION 3.25)

# Set your project name and C++ standard
project(Test CXX)
set(CMAKE_CXX_STANDARD 20)

# Enable CTest for testing
include(CTest)
enable_testing()

# Set additional compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion -Wall -Werror -Wextra -pedantic")

# Set the arm64 architecture as the target
set(CMAKE_OSX_ARCHITECTURES "arm64")

# Specify the output directory for the final executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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
add_executable(testAll ${OBJS})
target_link_options(testAll PRIVATE "-arch" "arm64")

# Add include directories if needed
target_include_directories(testAll PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/customMake)

# Set additional compiler flags
target_compile_options(testAll PRIVATE
        "-Wconversion"
        "-Wall"
        "-Werror"
        "-Wextra"
        "-pedantic"
        )

# Download and include Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
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
endforeach()

# Link rule to produce the test executable(s)
add_executable(testProgram ${TESTOBJS} ${OBJS})
target_link_options(testProgram PRIVATE "-arch" "arm64")
target_link_libraries(testProgram PRIVATE gtest gtest_main)

# Define ASSERT_TRUE macro if using Google Test
target_compile_definitions(testProgram PRIVATE USE_GTEST)

# Register the test with CTest
add_test(NAME MyTests COMMAND testProgram)
