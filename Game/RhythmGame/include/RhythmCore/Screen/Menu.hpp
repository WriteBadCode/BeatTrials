#pragma once

#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../GameManager.hpp"
#include "../../DataTypes.hpp"
#include "MyScreen.hpp"
#include "runSinglePlayer.hpp"

class Menu : public MyScreen {
    private:
        

    public:
        Menu()
        {
            this->init_config();
            
        }

        void init_config() override {
            float screenWidth = GameManager::desktopMode.width,
                screenHeight = GameManager::desktopMode.height;
            RectProps props = {screenWidth, screenHeight, {0, 0}};
            // load background
            this->m_sprites["menu_background"] = MySprite("menu_background.jpg", props);

            // props = {screenWidth / 10, screenHeight / 10, {screenWidth / 2, screenHeight / 2}};
            // // single player option sprite here
            // this->m_sprites["singlePlayerButton"] = MySprite("singlePlayerButton.jpg", props);

            // props = {screenWidth / 10, screenHeight / 10, {0, 500}};
            // // multi player option sprite here
            // this->m_sprites["multiPlayerButton"] = MySprite("multiPlayerButton", props);
            MyScreen::music = std::make_shared<sf::Music>();
            if (!MyScreen::music->openFromFile("C:/Users/5418m/cppFolder/BeatTrials/Game/RhythmGame/assets/audio/background_music.mp3")) {
                std::cerr << "Failed to load audio file" << std::endl;
                return;
            }

            // // this->music.setVolume(50.0f);
            MyScreen::music->setLoop(true);

        }

        void handleEvents(sf::Event& event) override {  
            while (this->window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    this->window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    this->handleOnPress(event);
                }
            }
        }

        void renderFrame() override {
            this->window.clear();
            // for (auto &pair : m_sprites) {
            //     this->window.draw(pair.second.getSprite());
            // }
            // const sf::Sprite &current_sprite = m_sprites["menu_background"].getSprite();
            // std::cout << current_sprite.getPosition().x << " " << current_sprite.getPosition().y << std::endl;
            // std::cout << current_sprite.getScale().x << " " << current_sprite.getScale().x << std::endl;
            // std::cout << current_sprite.getTexture();
            // system("pause");
            this->window.draw(m_sprites["menu_background"].getSprite());
            this->window.display();
        }
        
        void handleOnPress(sf::Event& event) {
            // if (m_sprites["singlePlayerButton"].getSprite().getGlobalBounds().contains(
            //     sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) 
            // {
            //     // this->music.pause();
            //     // call single player screen
            //     // this->music.play();
            // }

            // Check if mouse click is inside sprite2's bounds
            // else if (m_sprites["multiPlayerButton"].getSprite().getGlobalBounds().contains(
            //     sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) 
            // {
            //     this->music.pause();
            //     // call multi player screen
            //     this->music.play();
            // }
        }

        void run() override {
            MyScreen::music->play();
            while (this->window.isOpen()) 
            {
                // sf::Event event;
                // this->handleEvents(event);

                // handleFPS(this->clock, this->timePerFrame);

                // this->renderFrame();

                std::cout << "1. Single Player" << std::endl;
                std::cout << "2. Multi Player" << std::endl;
                int option = 0;
                std::cin >> option;
                switch (option) {
                    case 1:
                        // system("clear");
                        // run single player;
                        std::cout << "GOT HERE" << std::endl;
                        MyScreen::music->pause();
                        {
                            runSinglePlayer singlePlayer;
                            singlePlayer.run();
                        }
                        // some kidn of playing format
                        std::cout << "ENDS" << std::endl;
                        MyScreen::music->play();
                        break;
                    case 2:
                        system("clear");
                        // run multi player
                        break;
                }

                this->renderFrame();
                this->handleFPS(this->clock, this->timePerFrame);
            }
        }
};

void RThreadMain() {
    Menu menu;
    menu.run();
}