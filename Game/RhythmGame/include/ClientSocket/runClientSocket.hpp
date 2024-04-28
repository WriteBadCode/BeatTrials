#pragma once

#include <iostream>
#include "ClientHandler.hpp"
#include "../GameManager.hpp"

void runClientSocket() {
    GameManager::m_client.startSelf(GameManager::client_port);
};

