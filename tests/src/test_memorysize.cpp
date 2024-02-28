#include "gmock/gmock.h"
#include "CayenneLPP.hpp"

TEST(maxsizeTEST, Handles0input) {
    const uint8_t testval = 1;
    CayenneLPP::Measurement_t result = CayenneLPP::SetDigitalOutput(testval);
    EXPECT_EQ(result.val.DigitalGPIO, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_DIGITAL_OUTPUT);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);

    if (RUN_ALL_TESTS()) {}
    return 0;
}
