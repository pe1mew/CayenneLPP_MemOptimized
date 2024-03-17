enable_testing()

include(CTest)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.x
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# CMake 3.14+
FetchContent_MakeAvailable(googletest)

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_helpers src/test_helpers.cpp)

target_link_libraries(test_helpers gtest gmock CayenneLPP)

add_test(
        NAME test_helpers
        WORKING_DIRECTORY ${TEST_DIR}
        COMMAND test_helpers)
        
