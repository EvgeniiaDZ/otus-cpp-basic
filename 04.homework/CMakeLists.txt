cmake_minimum_required(VERSION 3.9)

project(calc CXX)

add_executable(calc
    src/lexer.cpp
    src/parser.cpp
    src/astnode.cpp
    src/main.cpp
    src/variable.cpp
    src/number.cpp
    src/add.cpp
    src/div.cpp
    src/mul.cpp
    src/sub.cpp
)

target_include_directories(calc PRIVATE include)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(calc PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(calc PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()

target_compile_features(calc PUBLIC cxx_std_17)
