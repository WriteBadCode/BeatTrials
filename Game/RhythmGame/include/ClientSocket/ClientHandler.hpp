#pragma once

#include <iostream>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using Conn = websocketpp::connection_hdl;

// could technically just use std::placeholders instead
using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

// Define a WebSocket client type
typedef websocketpp::client<websocketpp::config::asio> client;

// Define a handler class for WebSocket events
class ClientHandler
{
private:
    client self;
    client::connection_ptr con;

public:
    ClientHandler()
    {
        self.set_open_handler(bind(&ClientHandler::on_open, this, ::_1));
        self.set_close_handler(bind(&ClientHandler::on_close, this, ::_1));
        self.set_message_handler(bind(&ClientHandler::on_message, this, ::_1, ::_2));
    }

    void startSelf(std::string self_client_port) {
        websocketpp::lib::error_code ec;
        con = self.get_connection(self_client_port, ec);

        if (ec)
        {
            std::cout << "Error connecting to server: " << ec.message() << std::endl;
            return;
        }

        self.connect(con);
        self.run();
    }

    // Define event handlers
    void on_open(Conn hdl)
    {
        std::cout << "Connected to server." << std::endl;
    }

    void on_close(Conn hdl)
    {
        std::cout << "Disconnected from server." << std::endl;
    }

    void on_message(Conn hdl, client::message_ptr msg)
    {
        try
        {
            std::cout << "Received message: " << msg->get_payload() << std::endl;

            json jsonData = json::parse(msg->get_payload());

            if (jsonData["type"] == "communication") {
                jsonData["content"];
                // do something with the content
            }

            else if (jsonData["type"] == "room deletion") {
                // do something about not being in a room anymore
            }

        }
        catch (const std::exception &e)
        {
            std::cerr << "Error processing message: " << e.what() << std::endl;
        }
    }

    void send_message(std::string &msg)
    {
        self.send(con, msg, websocketpp::frame::opcode::text);
    }
};