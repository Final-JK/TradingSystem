#include "interface.h"
#include "kiwer_adapter.cpp"
#include "nemo_api_adapter.cpp"
#include "mock_driver.cpp"

#include <vector>

using std::vector;

class AutoTradingSystemFactory {
public:
	IStockerBrockerDriver* getTradingSystem(const string& id) {
		if (id == "Kiwer") return new KiwerAdapter();
		if (id == "Nemo") return new NemoAdapter();
		if (id == "Mock") return new MockDriver();
	}
};

class AutoTradingSystem {
public:
	enum Movement {
		INCREASE = 0,
		DECREASE = 1,
		NOTHING = 2
	};

public:
	AutoTradingSystem() = default;
	AutoTradingSystem(IStockerBrockerDriver* p_interface_stocker_brocker_driver):
		p_stocker_brocker_driver{ p_interface_stocker_brocker_driver }
	{}
	~AutoTradingSystem() {
		if (p_stocker_brocker_driver) {
			delete p_stocker_brocker_driver;
			p_stocker_brocker_driver = nullptr;
		}
	}
	void selectStockBrocker(const string& id) {
		if (p_stocker_brocker_driver) {
			delete p_stocker_brocker_driver;
			p_stocker_brocker_driver = nullptr;
		}
		p_stocker_brocker_driver = auto_trading_system_factory.getTradingSystem(id);
	}
	void login(const string& id, const string& password) {
		p_stocker_brocker_driver->login(id, password);
	}
	void buy(const string& stock_code, const int& count, const int& price) {
		p_stocker_brocker_driver->buy(stock_code, count, price);
	}
	void sell(const string& stock_code, const int& count, const int& price) {
		p_stocker_brocker_driver->sell(stock_code, count, price);
	}
	int getPrice(const string& stock_code, const int& minute) {
		return p_stocker_brocker_driver->getPrice(stock_code, minute);
	}

	void buyNiceTiming(const string& id, const int& total_price) {
		if (!p_stocker_brocker_driver) throw;

		auto price_data = getPriceData(id);
		if (checkMovement(price_data) == Movement::INCREASE) {
			int last_price = price_data[TRY_COUNT - 1];
			int count = total_price / last_price;
			p_stocker_brocker_driver->buy(id, count, last_price);
		}
	}

	void sellNiceTiming(const string& id, const int& num_of_stock) {
		auto price_data = getPriceData(id);
		if (checkMovement(price_data) == Movement::DECREASE) {
			int last_price = price_data[TRY_COUNT - 1];
			p_stocker_brocker_driver->sell(id, num_of_stock, last_price);
		}
	}

private:
	IStockerBrockerDriver* p_stocker_brocker_driver = nullptr;
	AutoTradingSystemFactory auto_trading_system_factory;

	const int TRY_COUNT = 3;
	const int FREQUENCY_MILLI_SECOND = 200;

	vector<int> getPriceData(const string& id) {
		int try_count = TRY_COUNT;
		vector<int> price_data = {};
		while (try_count--) {
			price_data.push_back(
				p_stocker_brocker_driver->getPrice(id, FREQUENCY_MILLI_SECOND));
		}

		return price_data;
	}

	Movement checkMovement(vector<int> price_data) {
		int first_price = *price_data.begin();
		Movement ret = Movement::NOTHING;

		for (auto price_iter = price_data.begin() + 1;
			price_iter != price_data.end();
			price_iter++) {
			int diff = first_price - *price_iter;
			if (diff < 0 && ret == Movement::NOTHING) {
				ret = Movement::INCREASE;
				first_price = *price_iter;
			}
			else if (diff > 0 && ret == Movement::NOTHING) {
				ret = Movement::DECREASE;
				first_price = *price_iter;
			}
			else {
				return Movement::NOTHING;
			}
		}
		return ret;
	}
};

