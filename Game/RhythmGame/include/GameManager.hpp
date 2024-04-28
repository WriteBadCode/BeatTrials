#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../include/ClientSocket/ClientHandler.hpp"

class GameManager {
public:
    static sf::RenderWindow window;
    static sf::VideoMode desktopMode;
    static int fps;
    static int lane_count;
    static int max_notes_per_lane;
    static float pixels_per_frame;
    static float pixels_per_tick;
    static float thick_frame;
    static float fixed_note_width;
    static sf::Color note_color;
    static std::string client_port;
    static ClientHandler m_client;

private:
    GameManager() {}
};

sf::RenderWindow GameManager::window(sf::VideoMode::getDesktopMode(), "SFML Window");
sf::VideoMode GameManager::desktopMode = sf::VideoMode::getDesktopMode();
int GameManager::fps = 60;

int GameManager::lane_count = 4;
int GameManager::max_notes_per_lane = 12;
sf::Color GameManager::note_color = sf::Color::Cyan;

std::string GameManager::client_port = "ws://localhost:9002";
ClientHandler GameManager::m_client;

float GameManager::thick_frame = GameManager::desktopMode.width * 0.025;

// (height / max notes per lane) * (notes per tick / fps)
float GameManager::pixels_per_frame = (GameManager::desktopMode.height / GameManager::max_notes_per_lane) 
                                        * (2.25 / GameManager::fps);

float GameManager::pixels_per_tick = GameManager::pixels_per_frame * GameManager::fps / 9;


float GameManager::fixed_note_width = GameManager::desktopMode.width / 2 / 4 - GameManager::thick_frame;