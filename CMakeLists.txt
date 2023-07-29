# Set the minimum macOS version required
cmake_minimum_required(VERSION 3.25)

# Set your project name and C++ standard
project(bs_from_scratch CXX)
set(CMAKE_CXX_STANDARD 20)

## Set the output extension for C++ object files
#set(CMAKE_CXX_OUTPUT_EXTENSION .o)

# Set additional compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion -Wall -Werror -Wextra -pedantic")

# Set the arm64 architecture as the target
set(CMAKE_OSX_ARCHITECTURES arm64)

add_subdirectory(src)
add_subdirectory(test)

# Add your main executable sources to the target (e.g., "bs" in this case)
add_executable(bs
        	   main.cpp
               Program.cpp
        	   inputReader.cpp
		src/blackScholesModel.cpp)


# Set the C++ standard library to libc++ (for macOS)
if (APPLE)
	target_link_options(bs PRIVATE -stdlib=libc++)
endif()

## Link the main executable with any necessary libraries
#target_link_libraries(bs PRIVATE libstdc++)
## include libcurl eventually

# Set the C++ standard for the main executable
target_compile_features(bs PRIVATE cxx_std_20)

## Set additional compiler flags for the target
#target_compile_options(bs PRIVATE -g3 -O3 -DDEBUG)

# Set additional compiler flags for the target
# The following CMake variables define configurations: CMAKE_CXX_FLAGS_DEBUG, CMAKE_CXX_FLAGS_RELEASE, CMAKE_CXX_FLAGS_RELWITHDEBINFO, CMAKE_CXX_FLAGS_MINSIZEREL
#target_compile_options(bs PRIVATE "$<$<CONFIG:Debug>:-g3 -DDEBUG>")
#target_compile_options(bs PRIVATE "$<$<CONFIG:Release>:-O3>")
#target_compile_options(bs PRIVATE "$<$<CONFIG:RelWithDebInfo>:-g3 -O3>")
#target_compile_options(bs PRIVATE "$<$<CONFIG:MinSizeRel>:-Os -g0 -finline-functions -flto -fomit-frame-pointer>")

# Define the test executable and link it with the test source file(s)
add_executable(test_bs tests/testProgram.cpp tests/testInputReader.cpp tests/testBlackScholesModel.cpp tests/testBlackScholesModel.cpp schlisselTest.h schlisselTest.cpp)
#add_executable(schlissel schlisselTest/schlissel.cpp)

# Add the path to the folder containing the custom test framework header
include_directories(schlisselTest)


# Set the C++ standard for the test executable
target_compile_features(test_bs PRIVATE cxx_std_20)

# Define ASSERT_TRUE macro if using Google Test
target_compile_definitions(test_bs PRIVATE schlisselTest)

## Set the C++ standard library to libc++ (for macOS)
#if (APPLE)
#	target_link_options(test_bs PRIVATE -stdlib=libc++)
#endif()
#
## Find and include Google Test
#find_package(GTest REQUIRED)
#
## Link the test executable against the Google Test library
#target_link_libraries(test_bs PRIVATE GTest::GTest GTest::Main)

## Define ASSERT_TRUE macro if using Google Test
#target_compile_definitions(test_bs PRIVATE USE_GTEST)

## Optionally, you can define your own ASSERT_TRUE macro
## Uncomment the following line if you want to define your own ASSERT_TRUE macro
#target_compile_definitions(test_bs PRIVATE ASSERT_TRUE(expr) if (!(expr)) { GTEST_FATAL_FAILURE_("Assertion failed: ") expr)

## Add a custom target for cleaning the build
#add_custom_target(clean COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
#        		        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR})

#enable_testing()
#add_test(NAME test_default_ctor COMMAND Program_tests.cpp)
#add_test(NAME test_get_opts COMMAND Program_tests.cpp)


#add_library(bs-from-scratch)
