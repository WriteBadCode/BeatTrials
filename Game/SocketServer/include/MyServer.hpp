#pragma once

#include <iostream>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "GameRoomManager.hpp"
#include "ClientInfo.hpp"
#include "GameRoom.hpp"

using json = nlohmann::json;
using Conn = websocketpp::connection_hdl;
using server = websocketpp::server<websocketpp::config::asio>;
using connection_map = std::unordered_map<Conn, ClientInfo *>;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

class MyServer
{
private:
    server m_server;
    connection_map m_connections;
    GameRoomManager game_room_manager;

public:
    MyServer()
    {
        m_server.init_asio();
        m_server.set_open_handler(std::bind(&MyServer::on_open, this, _1));
        m_server.set_message_handler(std::bind(&MyServer::on_message, this, _1, _2));
        m_server.set_close_handler(std::bind(&MyServer::on_close, this, _1));
    }

    void on_open(Conn hdl)
    {
        ClientInfo *new_client = new ClientInfo(hdl);
        m_connections[hdl] = new_client;
        std::cout << "New connection opened: " << hdl.lock() << std::endl;
    }

    void on_message(Conn hdl, server::message_ptr msg)
    {
        try
        {
            std::cout << "Received message: " << msg->get_payload() << std::endl;

            json jsonData = json::parse(msg->get_payload());

            // check if the connnection exists
            if (m_connections.find(hdl) != m_connections.end())
            {
                if (jsonData["type"] == "sign_up")
                { // then check if the client is busy or not
                    if (!m_connections[hdl]->getClientRoom())
                    {
                        GameRoom *new_game_room = game_room_manager.handleWaitList(m_connections[hdl]);
                        if (new_game_room)
                        {
                            std::vector<ClientInfo *> players = new_game_room->fetchPlayers();
                            for (auto *player : players)
                            {
                                m_connections[player->getSelfConnection()]->setClientRoom(new_game_room);
                            }
                        }
                    }
                }
                else if (jsonData["type"] == "exit room")
                {
                    if (!m_connections[hdl]->getClientRoom())
                    {
                        game_room_manager.deleteRoom(
                            m_connections[hdl]->getClientRoom()->getRoomNumber(),
                            m_server);
                    }
                }
                else if (jsonData["type"] == "communication")
                {
                    if (m_connections[hdl]->getClientRoom())
                    {
                        m_connections[hdl]->getClientRoom()->broadCastToOthers(
                            hdl,
                            "communication",
                            msg->get_payload(), // .dump is prob slower than raw string
                            m_server);
                    }
                }
            }
        }

        catch (const std::exception &e)
        {
            std::cerr << "Error processing message: " << e.what() << std::endl;
        }
    }

    void on_close(websocketpp::connection_hdl hdl)
    {
        if (!m_connections[hdl]->getClientRoom())
        {
            game_room_manager.deleteRoom(
                m_connections[hdl]->getClientRoom()->getRoomNumber(),
                m_server);
        }
        delete m_connections[hdl]; // free the client object memory first
        m_connections.erase(hdl);  // delete the rest of the bs.
    }

    void run()
    {
        m_server.listen(9002);
        m_server.start_accept();
        m_server.run();
    }

private:
    std::string generate_connection_id()
    {
        static int id_counter = 0;
        return std::to_string(id_counter++);
    }
};

// void broadcast_message(const std::string& msg) {
//     try {
//         for (const auto& connection_pair : m_connections) {
//             m_server.send(connection_pair.first, msg, websocketpp::frame::opcode::text);
//         }
//     } catch (const websocketpp::exception& e) {
//         std::cerr << "Error broadcasting message: " << e.what() << std::endl;
//     }
// }

// void send_message_to_connection(const std::string &connection_id, const std::string &msg)
// {
//     auto it = m_connections.find(connection_id);
//     if (it != m_connections.end())
//     {
//         try
//         {
//             m_server.send(it->second, msg, websocketpp::frame::opcode::text);
//         }
//         catch (const websocketpp::exception &e)
//         {
//             std::cerr << "Error sending message to connection " << connection_id << ": " << e.what() << std::endl;
//         }
//     }
//     else
//     {
//         std::cerr << "Connection " << connection_id << " not found" << std::endl;
//     }
// }
