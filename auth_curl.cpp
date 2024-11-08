#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/system/error_code.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>
#include <json/json.h>
#include <boost/asio.hpp>
#include <thread>

using namespace std;
using namespace json;

typedef websocketpp::client<websocketpp::config::asio_client> client;

class DeribitAuthClient {
public:
    DeribitAuthClient() {
        // Initialize WebSocket++ ASIO transport
        c.init_asio();
        c.set_message_handler(websocketpp::lib::bind(
            &DeribitAuthClient::on_message, this, websocketpp::lib::placeholders::_1,
            websocketpp::lib::placeholders::_2));
        c.set_open_handler(websocketpp::lib::bind(
            &DeribitAuthClient::on_open, this, websocketpp::lib::placeholders::_1));
        c.set_close_handler(websocketpp::lib::bind(
            &DeribitAuthClient::on_close, this, websocketpp::lib::placeholders::_1));
        c.set_fail_handler(websocketpp::lib::bind(
            &DeribitAuthClient::on_fail, this, websocketpp::lib::placeholders::_1));
    }

    void connect(const std::string &uri) {
        websocketpp::lib::error_code ec;
        auto con = c.get_connection(uri, ec);
        if (ec) {
            cout << "Connection error: " << ec.message() << endl;
            return;
        }

        hdl = con->get_handle();
        c.connect(con);

        // Launch the ASIO run loop in a new thread
        std::thread([this]() { c.run(); }).detach();
    }

    // Authentication message
    void authenticate() {
        Json::Value authMessage;
        authMessage["jsonrpc"] = "2.0";
        authMessage["id"] = 1;
        authMessage["method"] = "public/auth";
        authMessage["params"]["grant_type"] = "client_credentials";
        authMessage["params"]["client_id"] = "_xLmnrn2"; // Replace with your client ID
        authMessage["params"]["client_secret"] = "Z_4zIjmiBx6DHJfJDqoqJeMDarA_EAdW8KBVd0UFa4A"; // Replace with your client secret

        send_json_message(authMessage);
    }

private:
    client c;
    websocketpp::connection_hdl hdl;

    void on_open(websocketpp::connection_hdl hdl) {
        cout << "WebSocket connection opened." << endl;
        authenticate(); // Authenticate immediately on connection
    }

    void on_message(websocketpp::connection_hdl, client::message_ptr msg) {
        cout << "Received message: " << msg->get_payload() << endl;

        // Parse the JSON response to handle authentication success
        Json::CharReaderBuilder reader;
        Json::Value response;
        string errs;
        istringstream s(msg->get_payload());
        if (!Json::parseFromStream(reader, s, &response, &errs)) {
            cerr << "Failed to parse JSON: " << errs << endl;
            return;
        }

        // Check if the response contains a successful authentication
        if (response["id"].asInt() == 1) {
            if (response["result"].isObject() && !response["error"]) {
                cout << "Authentication successful!" << endl;
            } else {
                cerr << "Authentication failed: " << response["error"]["message"].asString() << endl;
            }
        }
    }

    void on_close(websocketpp::connection_hdl) {
        cout << "WebSocket connection closed." << endl;
    }

    void on_fail(websocketpp::connection_hdl) {
        cout << "WebSocket connection failed." << endl;
    }

    void send_json_message(const Json::Value &message) {
        Json::StreamWriterBuilder writer;
        string messageStr = Json::writeString(writer, message);
        c.send(hdl, messageStr, websocketpp::frame::opcode::text);
    }
};

int main() {
    DeribitAuthClient client;
    client.connect("wss://test.deribit.com/ws/api/v2");

    // Keep the main thread alive while the WebSocket is running
    this_thread::sleep_for(chrono::seconds(10));
    return 0;
}
