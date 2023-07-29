# Set the minimum macOS version required
cmake_minimum_required(VERSION 3.25)


# List all your source files here (excluding main.cpp)
set(SOURCES
        Program.h
        Program.cpp
        inputReader.h
        inputReader.cpp
        blackScholesModel.h
        blackScholesModel.cpp
        # Add more source files as needed
        )

# Add the executable target
add_executable(model ${SOURCES} main.cpp)

# Add include directories if needed
target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
