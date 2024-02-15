#include "gmock/gmock.h"

TEST(SOME_TEST_CLASS, SOME_TEST) {
EXPECT_EQ(1,1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);

    if (RUN_ALL_TESTS()) {}
    return 0;
}
