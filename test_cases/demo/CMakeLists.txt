cmake_minimum_required(VERSION 3.22)
project(demo)

set(CMAKE_CXX_STANDARD 17)

find_package(mpc_package REQUIRED)

add_executable(demo main.cpp
        test_cases.h)

target_link_directories(demo PUBLIC ${mpc_package_LIBRARY_DIRS})
target_link_libraries(demo mpc_package)
target_include_directories(demo PUBLIC ${mpc_package_INCLUDE_DIRS})
