#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"


using json = nlohmann::json;

typedef struct Position {
    float x, y;
}
Position;

typedef struct RectProps
{
    float width, height;
    Position position;
} RectProps;

typedef struct CircleProps
{
    float radius;
} CircleProps;

std::shared_ptr<json> toJsonMsg(std::string &type, const std::string &content) {
    std::shared_ptr<json> jsonData = std::make_shared<json>();
    (*jsonData)["type"] = type;
    (*jsonData)["content"] = content;
    return jsonData;
}

class MySprite {
    private:
        sf::Texture texture;
        sf::Sprite sprite;

    public:
        MySprite() {}

        MySprite(const std::string sprite_name, RectProps& props) {
            if (!this->texture.loadFromFile(
                "C:/Users/5418m/cppFolder/BeatTrials/Game/RhythmGame/assets/sprites/" +
                sprite_name
                )) {
                std::cout << "AINT THAT UNFORTUNATE" << std::endl;
                return;
            }
            
            
            this->sprite.setTexture(this->texture);
            this->sprite.setScale(100, 300);
            this->sprite.setPosition(props.position.x, props.position.y);

        }

        const sf::Sprite& getSprite() const {
            return this->sprite;
        }

        void setPosition(Position position) {
            this->sprite.setPosition(position.x, position.y);
        }

};

class MyRect
{
    private:
        sf::RectangleShape rectangle;

    public:
        // default constructor
        MyRect() {}

        // so we can pass Vector2f directly
        MyRect(const sf::Vector2f& rect_size) {
            this->rectangle.setSize(rect_size);
        }

        MyRect(const MyRect &otherRect) {
            this->rectangle = otherRect.getCpySelf();
        }

        const float& getHeight() const { return this->rectangle.getSize().y; }
        const float& getWidth() const { return this->rectangle.getSize().x; }
        void setHeight(float new_height) { 
            this->rectangle.setSize(sf::Vector2f(
                this->getWidth(),
                this->getHeight() + new_height
            )); 
        }
        void setWidth(float new_width) {
            this->rectangle.setSize(sf::Vector2f(
                this->getWidth() + new_width,
                this->getHeight()
            ));
        }
        void setSize(const sf::Vector2f& new_size) {
            this->rectangle.setSize(new_size);
        }

        const float& getX() const { return this->rectangle.getPosition().x; }
        const float& getY() const { return this->rectangle.getPosition().y; }
        void moveY(float new_y) {
            this->rectangle.setPosition(sf::Vector2f(
                this->getX(),
                this->getY() + new_y
            ));
        }

        void setPosition(const sf::Vector2f& new_position) {
            this->rectangle.setPosition(new_position);
        }

        void draw() {
            GameManager::window.draw(this->rectangle);
        }

        sf::RectangleShape& getRectSelf() {
            return this->rectangle;
        }

        const sf::RectangleShape& getCpySelf() const {
            return this->rectangle;
        }
};
