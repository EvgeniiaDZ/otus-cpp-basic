cmake_minimum_required(VERSION 3.9)

project(containerWithGTest CXX)

find_package(GTest)

add_executable(container
    source/main.cpp
)

target_include_directories(container PRIVATE include)

add_executable(
    test_container
    test/test_container.cpp
    test/vector_tests.cpp
    test/list_tests.cpp
    test/forward_list_tests.cpp
)

target_include_directories(
    test_container PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_include_directories(
    test_container PRIVATE
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(
    test_container PRIVATE
    ${GTEST_BOTH_LIBRARIES}
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(container PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
    target_compile_options(test_container PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(container PRIVATE
        /EHsc
        /W4
        /WX
    )
    target_compile_options(test_container PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()

# target_compile_features(container PUBLIC cxx_std_17)
