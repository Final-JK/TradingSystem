#include "interface.h"
#include "kiwer_api.cpp"

class KiwerAdapter : public IStockerBrockerDriver {
public:
	void login(string id, string password) override {

	}

	void buy(string stock_code, int count, int price) override {

	}

	void sell(string stock_code, int count, int price) override {

	}

	int getPrice(string stock_code, int minute = 0) override {

	}
private:
	KiwerAPI kiwer_api;
};