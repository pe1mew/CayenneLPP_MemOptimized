cmake_minimum_required(VERSION 3.11)
project(CayenneLPP_tests LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

set(CAYENNELPP_BUILD_TESTS YES)

add_library(CayenneLPP INTERFACE)

target_include_directories(CayenneLPP INTERFACE src/)

add_subdirectory(tests)
