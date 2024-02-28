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

add_executable(memorysize_test src/test_memorysize.cpp)

target_link_libraries(memorysize_test gtest gmock CayenneLPP)

add_test(
        NAME memorysize_test
        WORKING_DIRECTORY ${TEST_DIR}
        COMMAND memorysize_test)
        
