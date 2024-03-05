if (CAYENNELPP_BUILD_TESTS)
project(CayenneLPP_tests LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

enable_testing()

include(CTest)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.x
)

# CMake 3.14+
FetchContent_MakeAvailable(googletest)

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(memorysize_test src/test_memorysize.cpp)

add_test(
        NAME memorysize_test
        WORKING_DIRECTORY ${TEST_DIR}
        COMMAND memorysize_test)
        
endif()
