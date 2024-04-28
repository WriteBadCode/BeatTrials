#pragma once

#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../GameManager.hpp"
#include "../../DataTypes.hpp"


class MyScreen {

protected:
    sf::RenderWindow &window;
    std::unordered_map<std::string, MySprite> m_sprites;
    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.0f / 720.0f);

public:
    static std::shared_ptr<sf::Music> music;

    MyScreen() : window(GameManager::window) {}

    void handleFPS(sf::Clock& clock, sf::Time &timePerFrame) {
        sf::Time elapsedTime = clock.getElapsedTime();
        if (elapsedTime < timePerFrame)
        {
            sf::sleep(timePerFrame - elapsedTime);
        }
        clock.restart();
    }

    virtual void init_config() = 0;

    virtual void handleEvents(sf::Event& event) = 0;

    virtual void renderFrame() = 0;

    virtual void handleOnPress(sf::Event& event) = 0;

    virtual void run() = 0;
};

std::shared_ptr<sf::Music> MyScreen::music;