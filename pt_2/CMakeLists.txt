cmake_minimum_required(VERSION 3.12)
project(pt_2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
#add_link_options(-ldl)

add_subdirectory(pt_2_static)
add_subdirectory(pt_2_shared)

#add_definitions(-DSHARED)
add_executable(pt_2_sh main.c)
#remove_definitions(-DSHARED)

add_executable(pt_2_st main.c)
#add_executable(pt_2_mod main.c)

target_link_libraries (${PROJECT_NAME}_sh LINK_PUBLIC pt_2_shared_lib)
target_link_libraries (${PROJECT_NAME}_st LINK_PUBLIC pt_2_static_lib)