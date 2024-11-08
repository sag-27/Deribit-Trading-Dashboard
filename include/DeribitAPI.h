#pragma once

#include <string>

class DeribitAPI {
public:
    std::string place_order(const std::string& symbol, const std::string& type, double amount, double price);
    std::string cancel_order(const std::string& order_id);
    std::string modify_order(const std::string& order_id, double new_amount, double new_price);
    std::string get_order_book(const std::string& symbol);
    std::string get_current_positions(const std::string& currency, const std::string& kind);
};
