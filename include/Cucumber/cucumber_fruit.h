#pragma once

#include "SFML/Graphics.hpp"
using namespace sf;

class CucumberFruit{
private:
    float size = 0;
    float max_size = 25;
    float width = 8;
    float growth_rate = 10; 

    Vector2f position;
public:

    void grow(float, float);
    void SetPosition(Vector2f, float);

    float GetSize() { return size; }
    float GetWidth() { return width; }
    Vector2f GetPosition() { return position; }

};

void CucumberFruit::grow(float secondsPerDay, float deltaTime){
    size = size + (deltaTime * (growth_rate/secondsPerDay));
    if(size > max_size) size = max_size;
}

void CucumberFruit::SetPosition(Vector2f branch_pos, float branch_length){
    position = branch_pos + Vector2f(branch_length - (width / 2), 0);
}


