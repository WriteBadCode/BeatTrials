#pragma once

#include <iostream>
#include "GameRoom.hpp"

using Conn = websocketpp::connection_hdl;

class GameRoom;

class ClientInfo
{
    private:
        GameRoom *game_room;
        Conn self_connection;

    public:
        ClientInfo() : game_room(nullptr) {}
        ClientInfo(Conn &new_connection)
            : game_room(nullptr),
            self_connection(new_connection) {}


        void setClientRoom(GameRoom *room_address) {
            this->game_room = room_address;
        }

        Conn &getSelfConnection() {
            return this->self_connection;
        }

        GameRoom *getClientRoom() {
            return this->game_room;
        }
};
