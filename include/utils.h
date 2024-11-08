#pragma once

#include <string>
#include <curl/curl.h>
#include <iostream>

namespace UtilityNamespace {

    // Function declarations with modified names
    std::string postRequest(const std::string& endpoint, const std::string& data);
    std::string postRequestWithToken(const std::string& endpoint, const std::string& data, const std::string& token);
    std::string getRequest(const std::string& endpoint);
    std::string authenticateUser();
    void log(const std::string& message);

    // Callback function to handle data received from cURL
    static size_t WriteData(void* contents, size_t size, size_t nmemb, std::string* output);
}
