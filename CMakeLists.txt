set(CAYENNELPP_BUILD_TESTS NO)

add_library(CayenneLPP src/CayenneLPP.cpp)
target_include_directories(CayenneLPP PUBLIC src)
