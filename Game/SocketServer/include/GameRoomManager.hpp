#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <nlohmann/json.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <nlohmann/json.hpp>
#include "GameRoom.hpp"
#include "ClientInfo.hpp"
#include "../../RhythmGame/include/DataTypes.hpp"

using json = nlohmann::json;

// typedef websocketpp::server<websocketpp::config::asio> server;
using Conn = websocketpp::connection_hdl;
using room_map = std::unordered_map<int, GameRoom>;
using server = websocketpp::server<websocketpp::config::asio>;

// due to time constraints, we are going to make it an
// automatic fill system, where you don't get to create your own room
// (Game Room will be created whenever there are enough players)
#define ROOM_SIZE 2

class GameRoomManager
{
private:
    std::vector<ClientInfo *> wait_list;
    room_map mRooms;

public:
    GameRoomManager() {}

    GameRoom* create_room()
    {
        int new_room_id = generate_room_id();
        mRooms[new_room_id] = GameRoom(wait_list, new_room_id, ROOM_SIZE);
        return &mRooms[new_room_id];
    }


    // delete the room corresponding to room_id
    void deleteRoom(int room_id, server& m_server)
    {
        // write a death wish message (just means exiting the room )
        std::string type = "room deletion",
                    content = "deadge";
        std::string death_wish_message = toJsonMsg(type, content)->dump();
        GameRoom &room = mRooms[room_id];
        room.clearRoom(death_wish_message, m_server);
        mRooms.erase(room_id);  
        // return the room outside
        // and have the player memories clean from server.
    }

    GameRoom* handleWaitList(ClientInfo *player)
    {
        if (wait_list.size() + 1 == ROOM_SIZE) {
            return create_room();
        } else {
            wait_list.push_back(player);
            return nullptr;
        }
    }

private:
    int generate_room_id()
    {
        static int id_counter = 0;
        return id_counter++;
    }
};