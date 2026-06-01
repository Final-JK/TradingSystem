#pragma once

#include <string>
#define interface struct

using std::string;

interface IStockerBrockerDriver{
	virtual void login(string id, string password) = 0;
	virtual void buy(std::string stock_code, int count, int price) = 0;
	virtual void sell(std::string stock_code, int count, int price) = 0;
	virtual int getPrice(std::string stock_code, int minute = 0) = 0;
};
