cmake_minimum_required(VERSION 3.12)
project(unit_test C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER g++)
set(CMAKE_C_FLAGS "-fprofile-arcs -ftest-coverage -fPIC -O0 -pthread -Wpedantic")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_static test.c ../src/read.c ../src/count.c)
target_link_libraries(test_static ${GTEST_LIBRARIES})