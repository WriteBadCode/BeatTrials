#pragma once

#include <iostream>
#include "../../GameManager.hpp"

class Note {
    public:
        bool isActive;

        // all in ticks_per_second
        Note(float start=0.0, float end=0.0, float leeway = 0.0) 
        : rStart(start), rEnd(end), isActive(true) 
        {
            this->hStart = start + leeway;
            this->hEnd = end - leeway;
        } 

        float getRStart() const { return rStart; }

        void setRStart(float start) { rStart = start; }

        float getREnd() const { return rEnd; }

        void setREnd(float end) { rEnd = end; }

        float getHEnd() const { return hEnd; }

        void setHEnd(float end) { hEnd = end; }

        float getHStart() const{ return hStart; }

        void setHstart(float start) { hStart = start; }

        float decreaseByOneFrame() {
            return hStart -= GameManager::pixels_per_frame; 
        }

    private:
        float rStart, rEnd, hStart, hEnd;
};
        