cmake_minimum_required(VERSION 3.16)
project(oop_lab2_c18 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(matrix src/matrix.cpp)
target_include_directories(matrix PUBLIC src)
add_executable(oop_lab2 src/main.cpp)
target_link_libraries(oop_lab2 PRIVATE matrix)

include(CTest)
if(BUILD_TESTING)
    include(FetchContent)
    set(BUILD_GMOCK OFF CACHE BOOL "Build Google Mock")
    set(gtest_force_shared_crt ON CACHE BOOL "Use a shared Windows CRT")
    FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.18.0
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(googletest)
    add_executable(matrix_tests tests/matrix_test.cpp)
    target_link_libraries(matrix_tests PRIVATE matrix GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(matrix_tests)
endif()
