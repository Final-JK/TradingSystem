#include "inteface.cpp"
#include "gmock/gmock.h"

class MockDriver : public IStockerBrockerDriver {
public:
	MOCK_METHOD(void, login, (string id, string password), (override));
	MOCK_METHOD(void, buy, (std::string stock_code, int count, int price), (override));
	MOCK_METHOD(void, sell, (std::string stock_code, int count, int price), (override));
	MOCK_METHOD(int, getPrice, (std::string stock_code, int minute), (override));
};
