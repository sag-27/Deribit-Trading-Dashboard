#include "DeribitAPI.h"
#include "utils.h"
#include <json/json.h>

std::string DeribitAPI::place_order(const std::string& symbol, const std::string& type, double amount, double price) {
    std::string access_token = UtilityNamespace::authenticateUser();
    std::string url = "wss://test.deribit.com/ws/api/v2"; 

    Json::Value params;
    params["instrument_name"] = symbol;
    params["amount"] = amount;

    Json::Value payload;
    payload["jsonrpc"] = "2.0";
    payload["id"] = 12345; 

    if (type == "buy") {
        payload["method"] = "private/buy";
        params["type"] = "market"; 
    } else if (type == "sell") {
        payload["method"] = "private/sell";
        params["type"] = "stop_limit"; 
        params["price"] = price; 
        params["trigger_price"] = price - 1; 
        params["trigger"] = "last_price"; 
    } else {
        throw std::invalid_argument("Invalid order type. Use 'buy' or 'sell'.");
    }

    payload["params"] = params;

    // Authorization header with the access token
    std::string authHeader = "Authorization: Bearer " + access_token;

    return UtilityNamespace::postRequestWithToken(url, payload.toStyledString(), authHeader);
}

std::string DeribitAPI::cancel_order(const std::string& order_id) {
    std::string access_token = UtilityNamespace::authenticateUser();
    std::string url = "wss://test.deribit.com/ws/api/v2"; 

    Json::Value params;
    params["order_id"] = order_id;

    Json::Value payload;
    payload["jsonrpc"] = "2.0";
    payload["id"] = 23456; 

    payload["method"] = "private/cancel";
    payload["params"] = params;

    // Authorization header with the access token
    std::string authHeader = "Authorization: Bearer " + access_token;

    return UtilityNamespace::postRequestWithToken(url, payload.toStyledString(), authHeader);
}

std::string DeribitAPI::modify_order(const std::string& order_id, double new_amount, double new_price) {
    std::string access_token = UtilityNamespace::authenticateUser();
    std::string url = "wss://test.deribit.com/ws/api/v2"; 

    Json::Value params;
    params["order_id"] = order_id;
    params["amount"] = new_amount; 
    params["price"] = new_price; 

    Json::Value payload;
    payload["jsonrpc"] = "2.0";
    payload["id"] = 34567; 
    payload["method"] = "private/edit"; 
    payload["params"] = params;

    std::string authHeader = "Authorization: Bearer " + access_token;

    return UtilityNamespace::postRequestWithToken(url, payload.toStyledString(), authHeader);
}

std::string DeribitAPI::get_order_book(const std::string& symbol) {
    std::string access_token = UtilityNamespace::authenticateUser();
    std::string url = "wss://test.deribit.com/ws/api/v2"; 

    Json::Value params;
    params["instrument_name"] = symbol; 
    params["depth"] = 5; 

    Json::Value payload;
    payload["jsonrpc"] = "2.0";
    payload["id"] = 45678; 
    payload["method"] = "public/get_order_book"; 
    payload["params"] = params;

    std::string authHeader = "Authorization: Bearer " + access_token;

    return UtilityNamespace::postRequestWithToken(url, payload.toStyledString(), authHeader);
}

std::string DeribitAPI::get_current_positions(const std::string& currency, const std::string& kind) {
    std::string access_token = UtilityNamespace::authenticateUser(); 
    std::string url = "https://test.deribit.com/api/v2/private/get_positions"; 

    Json::Value params;
    params["currency"] = currency; 
    params["kind"] = kind;         

    Json::Value payload;
    payload["jsonrpc"] = "2.0"; 
    payload["method"] = "private/get_positions"; 
    payload["params"] = params; 
    payload["id"] = 56789; 
    payload["token"] = access_token; 

    return UtilityNamespace::postRequestWithToken(url, payload.toStyledString(), "Authorization: Bearer " + access_token);
}
