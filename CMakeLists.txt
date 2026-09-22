cmake_minimum_required(VERSION 3.16)

project(lab1_variant17 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(matrix_ops matrix_ops.cpp)
target_include_directories(matrix_ops PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(lab1 main.cpp)
target_link_libraries(lab1 PRIVATE matrix_ops)  

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.18.0
    GIT_SHALLOW TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(matrix_tests tests/test_variant.cpp)
target_link_libraries(matrix_tests PRIVATE matrix_ops GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(matrix_tests)