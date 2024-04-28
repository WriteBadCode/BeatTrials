#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GroupManager.hpp"
#include "Note/Note.hpp"
#include "../GameManager.hpp"
#include "../DataTypes.hpp"

using GroupOfRects = GroupManager<MyRect>;
using wrap_note = std::shared_ptr<Note>;
using wrap_rect = std::shared_ptr<MyRect>;

class Lane
{
private:
    MyRect lane;
    std::vector<wrap_note> mNotes;
    sf::Color lane_color;
    sf::Color current_lane_color;
    sf::Keyboard::Key self_key;
    GroupOfRects &renderedNotes;
    float deltaTime, fadeSpeed;
    bool timeToDitch;

public:
    Lane(RectProps &props, sf::Color lane_color, 
        sf::Keyboard::Key &self_key, GroupOfRects &renderedNotes)
        : deltaTime(0.0), 
        fadeSpeed(0.0), 
        lane_color(lane_color),
        current_lane_color(lane_color),
        self_key(self_key), 
        timeToDitch(false),
        renderedNotes(renderedNotes)
    {
        this->init_lane(props);
    }

    Lane(const Lane &other) 
        : deltaTime(other.deltaTime),
        fadeSpeed(other.fadeSpeed),
        lane_color(other.lane_color),
        current_lane_color(other.lane_color),
        self_key(other.self_key),
        timeToDitch(other.timeToDitch),
        renderedNotes(other.renderedNotes)
    {
        RectProps props = {other.lane.getWidth(), other.lane.getHeight(), {other.lane.getX(), other.lane.getY()}};
        this->init_lane(props);
    }

    void init_lane(RectProps &props) {
        std::cout << "Lane Width: " << props.width << std::endl;
        this->lane.setSize(sf::Vector2f(props.width, props.height));
        this->lane.setPosition(sf::Vector2f(props.position.x, props.position.y));
        this->lane.getRectSelf().setFillColor(lane_color);
        this->lane.getRectSelf().setOutlineThickness(GameManager::thick_frame);
        this->lane.getRectSelf().setOutlineColor(sf::Color(200, 200, 200));  // gray
    }

    void setRenderLane(GroupOfRects &renderedNotes) {
        this->renderedNotes = renderedNotes;
    }

    void startFadeEffect() {
        this->updateLaneColor(this->lane_color);
        sf::Clock clock;
        this->deltaTime = clock.restart().asSeconds();
        this->fadeSpeed = 100.f / 60; // Amount of transparency change per second
    }
    void changeFade() {
        this->current_lane_color.a -= static_cast<sf::Uint8>(fadeSpeed * deltaTime); // Decrease alpha component
        if (this->current_lane_color.a < 0)
        {
            this->current_lane_color.a = 0; // Ensure alpha doesn't become negative
        }
    }
    void updateLaneColor(sf::Color newColor) { this->lane.getRectSelf().setFillColor(newColor); }

    MyRect& getLaneRect() { return this->lane; }

    void init_notes_chain()
    {

        float x_pos = this->lane.getX();
        std::cout << "x pos: " << x_pos << std::endl;
        float width = this->lane.getWidth();
        std::cout << "width: " << width << std::endl;
        float top = this->lane.getY();
        std::cout << "top: " << top << std::endl;
        // y position + lane height = bottom of the lane
        float bottom = top + this->lane.getHeight();
        std::cout << "bottom: " << bottom << std::endl;

        float max_height = this->lane.getHeight(),
                current_height = 0.0,
                y_pos = 0.0;
        std::cout << "max height: " << max_height << std::endl;
        // system("pause");
        bool hasEnded = false;

        width -= GameManager::thick_frame;

        for (auto note : this->mNotes)
        {

            // render height
            float height = note->getREnd() - note->getRStart();

            // move to the bottom of the render note
            if (this->renderedNotes.getGroup().empty())
            {
                std::cout << "base" << std::endl;
                std::cout << note->getRStart() << std::endl;
                current_height += note->getRStart() - current_height;
            }
            else
            {
                std::cout << "gap" << std ::endl;
                float gap = this->renderedNotes.getBack().getY() - note->getRStart();
                current_height = current_height + gap;
            }

            std::cout << "current height: " << current_height << std::endl;
            std::cout << "Height: " << height << std::endl;
            // system("pause");
            if (current_height < top)
            {
                break;
            }
            else if (current_height + height < top)
            {
                // we aghve to flip the notes because start and end are different
                height = max_height - current_height;
                this->timeToDitch = false;
                hasEnded = true;
            }

            y_pos = max_height - current_height - height;

            wrap_rect new_rect = std::make_shared<MyRect>(
                sf::Vector2f(GameManager::fixed_note_width, height)
                );

            new_rect->setPosition(sf::Vector2f(x_pos, y_pos));

            new_rect->getRectSelf().setFillColor(GameManager::note_color);
            this->renderedNotes.appendItem(new_rect);

            if (hasEnded)
            {
                break;
            }
        }
        std::cout << "BACK END POINT: " << this->renderedNotes.getGroup().back()->getY() << std::endl;
        std::cout << "renderd size: " << this->renderedNotes.getSize() << std::endl;
        // system("pause");
    }

    bool updateFrame()
    {
        bool wasPressed = false;
        // handle lane color
        if (isPressed())
        {
            this->startFadeEffect();
            wasPressed = true;
            std::cout << "deleted" << std::endl;
            // if (this->renderedNotes.getSize()) {
            //     this->renderedNotes.pop_front();
            // }
            // if (this->mNotes.size()) {
            //     this->mNotes.erase(this->mNotes.begin());
            // }
        }
        else
        {
            this->changeFade();
        }

        this->updateRenderedNotes();
        return wasPressed;
    }

    bool updateRenderedNotes()
    {

        // if there's any notes left, decrease the hitbox by 1
        // if it's hitbox's start is <= hitbox's end, that means the hitbox is over
        // if (!mNotes.empty() && mNotes.back()->decreaseByOneFrame() <= mNotes.back()->getHEnd())
        // {
        //     int index = renderedNotes.getSize() - 1;
        //     mNotes.erase(mNotes.begin() + index);
        // }

        // make sure we only erase the note that ran out of render range
        // wrap_note &bottom_note = mNotes[0];
        // if (bottom_note->getRStart() <= bottom_note->getREnd())
        // {
        //     renderedNotes.getGroup().erase(renderedNotes.getGroup().begin());
        //     if (renderedNotes.getGroup().empty())
        //     {
        //         // nothing left to render = end of game?
        //         return true;
        //     }
        // }

        // moving movin the notes downwards by 1.0f
        for (auto rectangle : renderedNotes.getGroup())
        {
            // rectangle->setHeight(rectangle->getHeight() - 1.0f);
            rectangle->moveY(GameManager::pixels_per_frame);
        }

        // removing the excess render range for the bottom note
        // after it moves downward by 1.0f
        renderedNotes.getGroup()[0]->setHeight(renderedNotes.getGroup()[0]->getHeight() - 1.0f);

        std::cout << "half way point: updateRendered Notes" << std::endl;

        // deciding if we should adjust the render range for the top note
        // whether we should rendering the not-showing part of the note
        // or the next note
        if (mNotes.size() > renderedNotes.getSize())
        {
            float top = this->lane.getY();
            wrap_note next_note = mNotes[renderedNotes.getSize()];
            // if (!this->timeToDitch)
            // {
            //     MyRect &rectangle = *renderedNotes.getGroup().back();

            //     rectangle.setHeight(rectangle.getY() + 1.0f);
            //     rectangle.moveY(1.0f);

            //     // if the current rectangle's y position is the same as
            //     // the predicted note's render range's end
            //     // then we set timeToDitch to true
            //     if (rectangle.getY() == next_note->getREnd())
            //     {
            //         this->timeToDitch = true;
            //     }
            // }
            // this is else if
            if (this->renderedNotes.getBack().getY() - next_note->getRStart() >= top)
            {
                std::cout << "next note" << std::endl;
                MyRect new_rect(sf::Vector2f(
                    GameManager::fixed_note_width,
                    next_note->getREnd() - next_note->getRStart()));

                new_rect.setPosition(sf::Vector2f(this->lane.getX(), top));
                new_rect.getRectSelf().setFillColor(GameManager::note_color);
                renderedNotes.appendItem(new_rect);
                this->timeToDitch = false;
            }
        }

        std::cout << "pass rendered notes" << std::endl;
        return false;
    }

    GroupOfRects* getRenderLane()
    {
        return &this->renderedNotes;
    }

    bool isPressed()
    {
        return sf::Keyboard::isKeyPressed(this->self_key);
    }

    wrap_note getBack() {
        return mNotes.back();
    }

    void enqueue(wrap_note item)
    {
        mNotes.push_back(item);
    }

    void enqueue(float start, float end)
    {

        // e.what() says what and where went wrong, better for debugging
        try
        {
            wrap_note new_note = std::make_shared<Note>(start, end);
            mNotes.push_back(new_note);
        }
        catch (std::bad_alloc &e)
        {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            return; // return nullptr if the memory allocation fails
        }
    }

    void dequeue()
    {
        if (!isEmpty())
        {
            mNotes.erase(mNotes.begin());
        }
    }

    wrap_note front() const
    {
        if (!isEmpty())
        {
            return mNotes.front();
        }
        else
        {
            return nullptr;
        }
    }

    bool isEmpty() const
    {
        return mNotes.empty();
    }

    size_t size() const
    {
        return mNotes.size();
    }
};
