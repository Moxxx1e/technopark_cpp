cmake_minimum_required(VERSION 3.12)
project(pt_2_shared C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic -pthread")

set(SOURCES src/count.c src/read.c src/error_handler.c)
include_directories("include/")

add_subdirectory(unit_test)
add_library(${PROJECT_NAME}_lib SHARED ${SOURCES})
add_library(${PROJECT_NAME}_mod MODULE ${SOURCES})

target_include_directories (${PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories (${PROJECT_NAME}_mod PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})