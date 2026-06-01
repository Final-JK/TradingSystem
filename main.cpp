#include "gmock/gmock.h"
#include "nemo_api.cpp"
#include "kiwer_api.cpp"


TEST(TradingSystem, StartProject) {
    EXPECT_EQ(1, 1);
}

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

