#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Lane.hpp"
#include "Note/Note.hpp"
#include "GroupManager.hpp"
#include "../GameManager.hpp"
#include "../DataTypes.hpp"

using GroupOfRects = GroupManager<MyRect>;
using GroupOfLanes = GroupManager<GroupOfRects>;

using wrap_lane = std::shared_ptr<Lane>;

sf::Keyboard::Key keys[4] = {sf::Keyboard::D, sf::Keyboard::F, sf::Keyboard::J, sf::Keyboard::K};

class LaneManager
{

private:
    int ticks_per_second;
    RectProps m_props;
    std::vector<wrap_lane> mLanes;
    GroupOfLanes group_manager;
    bool lanes_status[4] = {false, false, false, false};

public:
    /// @param laneCount How many lanes are in the song.
    LaneManager(RectProps &props, int ticks_per_second)
        : m_props(props), ticks_per_second(ticks_per_second)
    {

        this->init_lanes(); // intiializing lanes

    }

    void init_lanes()
    {
        // width of each lane
        RectProps lane_props = this->m_props;
        lane_props.width /= GameManager::lane_count;

        std::cout << "BEFORE init of lane notes: " << this->group_manager.getSize() << std::endl;
        // create lanes
        for (int i = 0; i < GameManager::lane_count; i++)
        {

            lane_props.position.x = m_props.width / 4 * (i + 1);
            std::shared_ptr<GroupOfRects> new_render_lane = group_manager.append_item();
            // props needs to be readjusted for the correct
            // lane size, before passing in
            wrap_lane newLane = std::make_shared<Lane>(
                lane_props,
                sf::Color(128, 128, 128),
                keys[i],
                *new_render_lane
            );


            // after lane is initialized, get its render objects for rendering

            // appending the newLane into the lanes stack
            mLanes.push_back(newLane);
        }
        (*mLanes.back()).getLaneRect().setWidth(-GameManager::thick_frame);
    }

    void load_lanes()
    {
        std::cout << "AMOUNT OF LANES: " << mLanes.size() << std::endl;
        for (auto &lane : mLanes)
        {
            std::cout << "New Lane" << std::endl;
            lane->init_notes_chain();
            std::cout << lane->size() << std::endl;
        }
        std::cout << "AMOUNT OF LANES AFTER: " << mLanes.size() << std::endl;
    }

    void setTicksPerSecond(int ticks_per_second) { this->ticks_per_second = ticks_per_second; }

    const int& getTicksPerSecond() const { return this->ticks_per_second; }


    GroupOfLanes& getRenderGroup() { return group_manager; }

    void updateFrame()
    {
        bool wasPressed = false;
        for (int i = 0; i < 4; i++)
        {
            std::cout << "loop " << i << std::endl;
            if (this->mLanes[i]->updateFrame())
            {
                wasPressed = true;

                this->lanes_status[i] = true;
            }
        }

        std::cout << "Pass for loop" << std::endl;
        if (wasPressed)
        {
            // send a socket msg (for multi player version only)
        }
    }
    std::vector<wrap_lane> &getManagedLanes() { return this->mLanes; }

    wrap_lane &getLaneByIndex(int index) { return this->mLanes[index]; }

    void renderLanes()
    {
        for (auto &lane : this->mLanes)
        {
            std::cout << "BAD LANE" << std::endl;
            lane->getLaneRect().draw();
            std::cout << "x pos: " << lane->getLaneRect().getX() << std::endl;
            std::cout << "width: " << lane->getLaneRect().getWidth() << std::endl;
        }
    }
};