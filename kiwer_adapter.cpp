#include "interface.h"
#include "kiwer_api.cpp"
#include <Windows.h>

class KiwerAdapter : public IStockerBrockerDriver {
public:
	void login(string id, string password) override {
		kiwer_api.login(id, password);
	}

	void buy(string stock_code, int count, int price) override {
		kiwer_api.buy(stock_code, count, price);
	}

	void sell(string stock_code, int count, int price) override {
		kiwer_api.sell(stock_code, count, price);
	}

	int getPrice(string stock_code, int minute = 0) override {
		Sleep(minute);
		return kiwer_api.currentPrice(stock_code);
	}
private:
	KiwerAPI kiwer_api;
};