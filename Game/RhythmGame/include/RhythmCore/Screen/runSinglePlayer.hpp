#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../GameManager.hpp"
#include "../LaneManager.hpp"
#include "../../DataTypes.hpp"
#include "../SongInterpreter.hpp"
#include "../Screen/MyScreen.hpp"

using GroupOfRects = GroupManager<MyRect>;
using GroupOfLanes = GroupManager<GroupOfRects>;


class runSinglePlayer : public MyScreen
{
private:
    int frameCount;
    std::shared_ptr<LaneManager> lane_manager;

public:
    runSinglePlayer() : frameCount(0)
    {
        std::cout << "here" << std::endl;
        this->init_config();
        
    }

    //GM.window.create(sf::VideoMode(200, 200), "SFML works!");
    //sf::RenderWindow &window = GM.window;
    void init_config() override
    {
        RectProps props = {GameManager::desktopMode.width / 2, GameManager::desktopMode.height, {0.0, 0.0}};
        this->lane_manager = songInterpreter("Lost_Woods", props);
        std::cout << "pass interpreter" << std::endl;

        this->lane_manager->load_lanes();
        std::cout << "pass init lanes" << std::endl;

        GroupOfLanes &rendered_lanes = lane_manager->getRenderGroup();
        for (auto lane : rendered_lanes.getGroup()) {
            std::cout << "lane size: " << lane->getSize() << std::endl;
        }

        // system("pause");

        Position position = {0, 0};

        // this->m_sprites["rhythm_game_background"] = MySprite("rhythm_game_background.png", position);
        MyScreen::music = std::make_shared<sf::Music>();
        if (!MyScreen::music->openFromFile("C:/Users/5418m/cppFolder/BeatTrials/Game/RhythmGame/assets/audio/Lost_Woods.mp3")) {
            std::cerr << "Failed to load audio file" << std::endl;
            return;
        } else {
            std::cout << "FREEDOM" << std::endl;
        }
    }

    void handleEvents(sf::Event& event) override
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }

            else if (event.type == sf::Event::MouseButtonPressed) {
                this->handleOnPress(event);
            }
                
        }
    }

    void renderFrame () override {}

    void renderFrame(GroupOfLanes &group_manager) 
    {
        this->window.clear();
        // window.draw(shape);
        // this->window.draw(m_sprites["rhythm_game_background"].getSprite());
        this->lane_manager->renderLanes();
        std::cout << "rendering" << std::endl;
        group_manager.draw();
        // system("pause");

        this->window.display();
        
    }

    void handleOnPress(sf::Event& event) override
    {
        // handling some kind of button
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            
        }
    }

    void run() override
    {
        // start playing music

        bool hasEnded = false;
        std::cout << "??" << std::endl;
        // system("pause");
        MyScreen::music->play();
        // system("pause");
        
        for (auto lane_notes : this->lane_manager->getRenderGroup().getGroup()) {
            std::cout << "start of lane" << std::endl;
            std::cout << "their size: " << (*lane_notes).getSize() << std::endl;
            for (auto notes : (*lane_notes).getGroup()) {
                std::cout << "note" << std::endl;
            }
            std::cout << "end of lane" << std::endl;
        }

        // system("pause");

        while (window.isOpen() && !hasEnded)
        {
            sf::Event event;
            this->handleEvents(event);

            std::cout << "pass event" << std::endl;

            this->lane_manager->updateFrame();

            std::cout << "pass updateFrame" << std::endl;

            GroupOfLanes &rythm_core = this->lane_manager->getRenderGroup();

            std::cout << "pass get render group " << std::endl;

            this->renderFrame(rythm_core);

            std::cout << "pass render frame " << std::endl;

            frameCount++;

            // fps
            this->handleFPS(this->clock, this->timePerFrame);

            // delete group manager.
        }
    }
};
