cmake_minimum_required(VERSION 3.9)

project(05.homework)

add_executable(statistics 
    source/statistics.cpp
    source/max.cpp
    source/min.cpp
    source/mean.cpp 
    source/std.cpp
)

target_include_directories(statistics PRIVATE include)

set_target_properties(statistics PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)