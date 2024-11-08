#pragma once

#include <string>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;


class WebSocketServer {
public:
    void start_server(int port);
    static void on_message(server* s, websocketpp::connection_hdl hdl, server::message_ptr msg);
};
