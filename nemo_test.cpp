#include "gmock/gmock.h"
#include "nemo_api_adapter.cpp"

#define USING_MOCK 1
using namespace testing;

#if (1 == USING_MOCK)
#include "mock_driver.cpp"
#endif

//=======================
// 네모 드라이버 test항목

TEST(TradingSystemNemoDriver, loginTest) {
    std::string expect = "[NEMO] A-team login GOOD\n";
    std::string ID = "A-team";
    std::string PASSWD = "1234";


    std::ostringstream oss; // 임시 buffer생성
    auto oldCoutStreamBuf = std::cout.rdbuf(); // 기존 cout의 출력 buffer 임시 저장
    std::cout.rdbuf(oss.rdbuf());  // cout의 출력을 임시 buffer로 바꿔놓기

#if (1 == USING_MOCK)
    NiceMock<MockDriver> mockDrv;

    EXPECT_CALL(mockDrv, login(_, _))
        .Times(1);
    oss << expect;

    mockDrv.login(ID, PASSWD);
#else
    IStockerBrockerDriver* nemoDrv = new NemoAdapter();
    nemoDrv->login(ID, PASSWD);
#endif

    std::cout.rdbuf(oldCoutStreamBuf); // 기존 cout의 출력 buffer되돌려 놓기

    EXPECT_THAT(oss.str(), Eq(expect));

}

TEST(TradingSystemNemoDriver, buyTest) {
    // buy 가 되는지 체크한다.
    std::string expect = "[Nemo] A-team : buy stock ( price : 1234 ) * ( count : 100000)\n";
    std::string STOCKCODE = "A-team";
    int PRICE = 1234;
    int COUNT = 100000;


    std::ostringstream oss; // 임시 buffer생성
    auto oldCoutStreamBuf = std::cout.rdbuf(); // 기존 cout의 출력 buffer 임시 저장
    std::cout.rdbuf(oss.rdbuf());  // cout의 출력을 임시 buffer로 바꿔놓기

#if (1 == USING_MOCK)
    NiceMock<MockDriver> mockDrv;

    EXPECT_CALL(mockDrv, buy(_, _, _))
        .Times(1);
    oss << expect;

    mockDrv.buy(STOCKCODE, COUNT, PRICE);
#else
    IStockerBrockerDriver* nemoDrv = new NemoAdapter();
    nemoDrv->buy(STOCKCODE, COUNT, PRICE);
#endif

    std::cout.rdbuf(oldCoutStreamBuf); // 기존 cout의 출력 buffer되돌려 놓기

    EXPECT_THAT(oss.str(), Eq(expect));

}

TEST(TradingSystemNemoDriver, sellTest) {
    // sell 이 되는지 체크한다.
    std::string expect = "[NEMO] A-team : sell stock ( price : 1234 ) * ( count : 100000)\n";
    std::string STOCKCODE = "A-team";
    int PRICE = 1234;
    int COUNT = 100000;


    std::ostringstream oss; // 임시 buffer생성
    auto oldCoutStreamBuf = std::cout.rdbuf(); // 기존 cout의 출력 buffer 임시 저장
    std::cout.rdbuf(oss.rdbuf());  // cout의 출력을 임시 buffer로 바꿔놓기

#if (1 == USING_MOCK)
    NiceMock<MockDriver> mockDrv;

    EXPECT_CALL(mockDrv, sell(_, _, _))
        .Times(1);
    oss << expect;

    mockDrv.sell(STOCKCODE, COUNT, PRICE);
#else
    IStockerBrockerDriver* nemoDrv = new NemoAdapter();
    nemoDrv->sell(STOCKCODE, COUNT, PRICE);
#endif

    std::cout.rdbuf(oldCoutStreamBuf); // 기존 cout의 출력 buffer되돌려 놓기

    EXPECT_THAT(oss.str(), Eq(expect));
}

TEST(TradingSystemNemoDriver, getPriceTest) {
    // getPrice 가 되는지 체크한다.
    std::string STOCKCODE = "A-team";
    int expect = 100;
    int returnValue = -1;

    std::ostringstream oss; // 임시 buffer생성
    auto oldCoutStreamBuf = std::cout.rdbuf(); // 기존 cout의 출력 buffer 임시 저장
    std::cout.rdbuf(oss.rdbuf());  // cout의 출력을 임시 buffer로 바꿔놓기

#if (1 == USING_MOCK)
    NiceMock<MockDriver> mockDrv;

    EXPECT_CALL(mockDrv, getPrice(_, _))
        .Times(1)
        .WillRepeatedly(Return(100));

    returnValue = mockDrv.getPrice(STOCKCODE, 1);
#else
    IStockerBrockerDriver* nemoDrv = new NemoAdapter();
    returnValue = nemoDrv->getPrice(STOCKCODE);
#endif

    std::cout.rdbuf(oldCoutStreamBuf); // 기존 cout의 출력 buffer되돌려 놓기

    EXPECT_THAT(returnValue, Eq(expect));
}
