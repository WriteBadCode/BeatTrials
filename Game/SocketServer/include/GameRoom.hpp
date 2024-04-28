#pragma once

#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include "ClientInfo.hpp"
#include "../../RhythmGame/include/DataTypes.hpp"

// typedef websocketpp::server<websocketpp::config::asio> server;
using Conn = websocketpp::connection_hdl;
using Players = std::vector<ClientInfo *>;
using server = websocketpp::server<websocketpp::config::asio>;

class ClientInfo;

// let's make it a fixed 2 players room
class GameRoom
{
private:
    Players players;
    int room_number;

public:
    GameRoom() : room_number(-1) {}
    GameRoom(Players &new_players, int room_number, int max_room_size)
        : room_number(room_number)
    {
        int index = 0; // Declare index outside the loop
        for (auto it = new_players.begin();
             it != new_players.end() && index < max_room_size;)
        {
            this->players.push_back(*it);
            it = new_players.erase(it); // Erase the element and update iterator
            index++;                    // Increment index
        }
    }

    ~GameRoom()
    {
    }

    std::vector<ClientInfo *> &fetchPlayers()
    {
        return players;
    }

    int getRoomNumber() const
    {
        return room_number;
    }

    void clearRoom(std::string &msg, server &m_server)
    {
        for (auto *player : players)
        {
            // broad cast to all players
            {
                m_server.send(
                    player->getSelfConnection(),
                    msg,
                    websocketpp::frame::opcode::text);
            }

            player->setClientRoom(nullptr);
        }
    }

    void broadCastToOthers(Conn &hdl, std::string type, 
        const std::string &info, server &m_server)
    {
        std::string msg = toJsonMsg(type, info)->dump();
        for (auto *player : players)
        {
            // broad cast the message to all players
            // in the current room, except for the original sender.
            if (player->getSelfConnection().lock() != hdl.lock())
            {
                m_server.send(
                    player->getSelfConnection(),
                    msg,
                    websocketpp::frame::opcode::text);
            }
        }
    }
};