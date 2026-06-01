#pragma once
#include "interface.h"
#include "nemo_api.cpp"

class NemoAdapter : public IStockerBrockerDriver {
public:
	void login(string id, string password) override {
		nemoApi.certification(id, password);
	};
	void buy(string stock_code, int count, int price) override {
		nemoApi.purchasingStock(stock_code, price, count);
	};
	void sell(string stock_code, int count, int price) override {
		nemoApi.sellingStock(stock_code, price, count);
	};
	int getPrice(string stock_code, int minute = 0) override {
		return nemoApi.getMarketPrice(stock_code, minute);
	};
private:
	NemoAPI nemoApi;
};