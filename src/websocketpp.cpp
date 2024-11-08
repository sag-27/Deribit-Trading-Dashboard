#include "websocketpp.h"
#include "DeribitAPI.h"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>
#include <string>

using namespace std;

typedef websocketpp::server<websocketpp::config::asio> server;

void WebSocketServer::on_message(server* s, websocketpp::connection_hdl hdl, server::message_ptr msg) {
    std::string symbol = msg->get_payload();
    DeribitAPI api;
    std::string orderBookData = api.get_order_book(symbol);
    s->send(hdl, orderBookData, websocketpp::frame::opcode::text);
}


void WebSocketServer::start_server(int port) {
    server ws_server;

    ws_server.init_asio();
    ws_server.set_message_handler(std::bind(&WebSocketServer::on_message, &ws_server, std::placeholders::_1, std::placeholders::_2));

    ws_server.listen(port);
    ws_server.start_accept();
    ws_server.run();
}
