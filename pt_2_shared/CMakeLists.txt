cmake_minimum_required(VERSION 3.12)
project(pt_2_shared C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic -pthread")

set(SOURCES src/count.c src/read.c)
include_directories("include/")

add_subdirectory(unit_test)
add_library(${PROJECT_NAME}_lib SHARED ${SOURCES})