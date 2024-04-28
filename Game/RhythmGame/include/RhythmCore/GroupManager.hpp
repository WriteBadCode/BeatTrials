#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../GameManager.hpp"

template <typename T>
class GroupManager
{
private:
    std::vector<std::shared_ptr<T>> mGroup;
public:
    std::shared_ptr<T> append_item() {
        std::shared_ptr<T> new_item = std::make_shared<T>();
        mGroup.push_back(new_item);
        return new_item;
    }

    void appendItem(std::shared_ptr<T> new_item) {
        mGroup.push_back(new_item);
    }

    void appendItem(const T& item)
    {
        std::shared_ptr<T> new_item = std::make_shared<T>(item);
        mGroup.push_back(new_item);
    }

    void appendItem(T* item) {
        this->appendItem(*item);
    }

    std::vector<std::shared_ptr<T>>& getGroup() {
        return mGroup;
    }

    T& getBack() {
        return *mGroup.back();
    }

    T& getFront() {
        return *mGroup.front();
    }

    int getSize() {
        return this->mGroup.size();
    }

    void draw()
    {
        if (this->getSize()){
            std::cout << "calling draw here" << std::endl;
            std::cout << this->getSize() << std::endl;
        }
        for (auto item : mGroup) {
            item->draw();
        }
    }

    void pop_index(int index) {
        mGroup.erase(mGroup.begin() + index);
    }
    
    void pop_front() {
        mGroup.erase(mGroup.begin());
    }

};
