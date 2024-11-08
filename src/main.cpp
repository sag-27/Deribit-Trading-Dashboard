#include "DeribitAPI.h"
#include "utils.h"
#include <iostream>

int main() {
    DeribitAPI orderManager;

    try {
        std::string token = UtilityNamespace::authenticateUser();
        std::cout << "Token: " << token << std::endl;

        // Place an order
        std::string response1 = orderManager.place_order("ETH-PERPETUAL", "buy", 1.0, 30000.0);
        std::cout << "Place Order Response: " << response1 << std::endl;

        // Cancel an order
        std::string orderId = "29119672418";
        std::string response2 = orderManager.cancel_order(orderId);
        std::cout << "Cancel Order Response: " << response2 << std::endl;

        // Modify an order
        std::string response3 = orderManager.modify_order(orderId, 2.0, 32000.0);
        std::cout << "Modify Order Response: " << response3 << std::endl;

        // Get Order Book
        std::string response4 = orderManager.get_order_book("ETH-PERPETUAL");
        std::cout << "Order Book Response: " << response4 << std::endl;

        // Get Current Positions
        std::string response5 = orderManager.get_current_positions("ETH", "future");     // option, future, spot
        std::cout << "Current Positions Response: " << response5 << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "Press Enter to exit...";
    std::cin.get();
    return 0;
}
