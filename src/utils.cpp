#include "utils.h"
#include "credentials.h" 
#include <curl/curl.h>
#include <iostream>
#include <json/json.h>

using namespace std;
using namespace Json;


namespace UtilityNamespace {

    // Callback function to write data received from cURL to a string
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* s) {
        size_t newLength = size * nmemb;
        s->append((char*)contents, newLength);
        return newLength;
    }

    string postRequest(const string& url, const string& payload) {
        CURL* curl;
        CURLcode res;
        string readBuffer;

        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        if (curl) {
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, "Content-Type: application/json");

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);

            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
        return readBuffer;
    }

    string postRequestWithToken(const string& endpoint, const string& data, const string& token) {
        CURL* curl;
        CURLcode res;
        string readBuffer;

        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        if (curl) {
            struct curl_slist* headers = nullptr;
            headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());
            headers = curl_slist_append(headers, "Content-Type: application/json");

            curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);

            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
        return readBuffer;
    }


    string authenticateUser() {
        string url = "https://test.deribit.com/api/v2/public/auth";
        string payload = "{\"jsonrpc\":\"2.0\", \"method\":\"public/auth\", \"params\":{\"grant_type\":\"client_credentials\", \"client_id\":\"" + API_KEY + "\", \"client_secret\":\"" + SECRET_KEY + "\"}, \"id\":1}";

        // POST request to authenticate
        string response = postRequest(url, payload);
        
        // parsing the response to get the access token
        Value json_response;
        Reader reader;
        if (!reader.parse(response, json_response)) {
            cerr << "Failed to parse response: " << response << endl;
            throw runtime_error("Authentication failed.");
        }

        if (json_response.isMember("result") && json_response["result"].isMember("access_token")) {
            string access_token = json_response["result"]["access_token"].asString();
            cout << "Access Token: " << access_token << endl;
            return access_token;
        } else {
            cerr << "Authentication failed. Response: " << response << endl;
            throw runtime_error("Authentication failed.");
        }
    }

}
