cmake_minimum_required(VERSION 3.25)
project(BSFromScratch CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the source files for the main project
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
	add_executable(${obj_name} ${CMAKE_SOURCE_DIR}/${src})
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

# Uncomment the following line if you want to define your own ASSERT_TRUE macro
#target_compile_definitions(test_bs PRIVATE ASSERT_TRUE(expr) if (!(expr)) { GTEST_FATAL_FAILURE_("Assertion failed: ") expr)

# Uncomment if you want to enable unit tests
enable_testing()

# Define the source files used in the test programs
set(TESTSRCS
		gtest.cpp
		test/testProgram.cpp
		include/customMake/unit_test_framework.h
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
	add_executable(${obj_name} ${CMAKE_SOURCE_DIR}/${src})
endforeach()

# Link rule to produce the test executable(s)
add_executable(bs_test ${TESTOBJS} ${SRCS})
target_link_options(bs_test PRIVATE "-arch" "arm64")
target_link_libraries(bs_test PRIVATE gtest gtest_main)

# Define ASSERT_TRUE macro if using Google Test
target_compile_definitions(bs_test PRIVATE USE_GTEST)

# Register the test with CTest
add_test(NAME default_ctor COMMAND bs_test)

# Optionally, you can define your own ASSERT_TRUE macro
# Uncomment the following line if you want to define your own ASSERT_TRUE macro
# target_compile_definitions(runUnitTests PRIVATE ASSERT_TRUE(expr) if (!(expr)) { GTEST_FATAL_FAILURE_("Assertion failed: ") expr)

# Optionally, you can define your own ASSERT_TRUE macro
# Uncomment the following line if you want to define your own ASSERT_TRUE macro
# target_compile_definitions(runUnitTests PRIVATE ASSERT_TRUE(expr) if (!(expr)) { GTEST_FATAL_FAILURE_("Assertion failed: ") expr)

#
## Set the output directory for executables to 'bin'
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#
## Add the 'src' subdirectory for your main project source files
#add_subdirectory(src)
#
## Add the 'test' subdirectory for unit tests
#add_subdirectory(test)
#
### Add the 'data' subdirectory for input data files
##add_subdirectory(data)
#
## Add a subdirectory for Google Test (GTest)
#add_subdirectory(deps/googletest)
#
## Add any additional subdirectories here (if needed)
## ...
#
## Set additional compiler flags for all targets
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wconversion -Wall -Werror -Wextra -pedantic")
#
## Set the target architecture to arm64 for macOS
#set(CMAKE_OSX_ARCHITECTURES arm64)
#
## Add your main executable sources to the target (e.g., "bs" in this case)
#add_executable(bs main.cpp src/Program.cpp src/inputReader.cpp src/blackScholesModel.cpp)
#
## Add a custom target for cleaning the build
#add_custom_target(clean_target COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
#		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR})
#
## Include directories for your library and custom test framework
#include_directories(
#		include
#		include/customMake
#		deps/gtest
#)
#
## Link Google Test to your main project and tests
#target_link_libraries(bs PRIVATE gtest gtest_main)
#
## Copy the contents of the data directory to the build directory
#file(COPY data DESTINATION ${CMAKE_BINARY_DIR})
#
## Set the C++ standard library to libc++ (for macOS)
#if (APPLE)
#	target_link_options(bs PRIVATE -stdlib=libc++)
#endif()
#
### include libcurl eventually
#
## Set the C++ standard for the main executable
#target_compile_features(bs PRIVATE cxx_std_20)
#
## Set additional compiler flags for the target
## The following CMake variables define configurations: CMAKE_CXX_FLAGS_DEBUG, CMAKE_CXX_FLAGS_RELEASE, CMAKE_CXX_FLAGS_RELWITHDEBINFO, CMAKE_CXX_FLAGS_MINSIZEREL
#target_compile_options(bs PRIVATE "$<$<CONFIG:Debug>:-g3 -DDEBUG>")
#target_compile_options(bs PRIVATE "$<$<CONFIG:Release>:-O3>")
#target_compile_options(bs PRIVATE "$<$<CONFIG:RelWithDebInfo>:-g3 -O3>")
#target_compile_options(bs PRIVATE "$<$<CONFIG:MinSizeRel>:-Os -g0 -finline-functions -flto -fomit-frame-pointer>")
#
## Optionally, you can generate a Makefile or IDE project files for users
## For example, for Makefile:
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
## For example, for Xcode:
#set(CMAKE_XCODE_GENERATE_SCHEME ON)
#
## You can install your project files if needed (optional)
#install(TARGETS your_executable DESTINATION bin)

# Uncomment the following line if you want to define your own ASSERT_TRUE macro
#target_compile_definitions(test_bs PRIVATE ASSERT_TRUE(expr) if (!(expr)) { GTEST_FATAL_FAILURE_("Assertion failed: ") expr)

# Uncomment if you want to enable unit tests
#enable_testing()
#add_test(NAME test_default_ctor COMMAND testProgram.cpp)
#add_test(NAME test_get_opts COMMAND testProgram.cpp)