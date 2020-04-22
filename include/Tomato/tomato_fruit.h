#pragma once

#include "SFML/Graphics.hpp"
using namespace sf;
//#include <tomato_branch.h>

class TomatoFruit{
private:
    float radius = 0;
    float max_radius = 7.5;
    float growth_rate = 3.75; 

    Vector2f position;
public:

    void grow(float, float);
    void SetPosition(Vector2f, float);

    float GetRadius() { return radius; }
    Vector2f GetPosition() { return position; }

};

void TomatoFruit::grow(float secondsPerDay, float deltaTime){
    radius = radius + (deltaTime * (growth_rate/secondsPerDay));
    if(radius > max_radius) radius = max_radius;
}

void TomatoFruit::SetPosition(Vector2f branch_pos, float branch_length){
    position = branch_pos + Vector2f(branch_length - radius, 0);
}


