cmake_minimum_required(VERSION 3.1)
project(optisearch)

# Setting flags.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/bin")
set(LIBRARY_OUTPUT_PATH    "${PROJECT_SOURCE_DIR}/build/lib")

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

# Creating the optisearch-common library.
set(SOURCES src/search.cpp
            src/board.cpp
            src/maze.cpp)

add_library(optisearch-common ${SOURCES})

# Setting up the executables themselves.
add_executable(optisearch src/main.cpp)
add_executable(optisearch-test src/testsetup.cpp src/test.cpp)

# Linking the libraries to the main & test executables.
target_link_libraries(optisearch optisearch-common)
target_link_libraries(optisearch-test optisearch-common)
