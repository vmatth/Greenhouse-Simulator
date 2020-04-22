#pragma once

#include <cucumber_fruit.h>

class CucumberBranch
{
private:
    float length = 0.0;
    float width = 5.0;
    float max_length = 15.0;
    float growth_rate = 4.0; //Length per day
    int side = 1; //Left = -1, Right = 1
    Vector2f position;
    
    CucumberFruit fruit;
public:
    CucumberBranch(int, Vector2f);

    void grow(float, float);
    float GetWidth() { return width; }
    float GetLength() { return length; }
    Vector2f GetPosition() { return position; }
    CucumberFruit GetFruit() { return fruit; }
};


void CucumberBranch::grow(float secondsPerDay, float deltaTime){
    length = length + (deltaTime * (growth_rate/secondsPerDay)) * side;
    if(abs(length) > max_length){
        length = max_length * side;  
        fruit.grow(secondsPerDay, deltaTime);
        fruit.SetPosition(position, length);
    }
}

CucumberBranch::CucumberBranch(int s, Vector2f pos){
    side = s;
    position = pos;
}

