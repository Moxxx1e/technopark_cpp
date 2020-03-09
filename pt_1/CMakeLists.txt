cmake_minimum_required(VERSION 3.13)
project(pt_1)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(pt_1 filter.c
        filter.h
        header.h
        list.c
        list.h
        main.c
        read.c
        read.h)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#add_executable(test
 #       filter.h
  #      test.cpp)
#target_link_libraries(test ${GTEST_LIBRARIES} pthread)