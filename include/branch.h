#pragma once


#include "SFML/Graphics/Color.hpp"

using namespace sf;

class Branch{
private:
    float length = 0.0;
    float width = 5.0;
    float max_length = 25.0;
    const float growth_rate = 5.0; //Length per day
    int side = 1; //Left = -1, Right = 1
    Vector2f position;
public:
    void grow(float, float);
    float GetWidth() { return width; }
    float GetLength() { return length; }
    Vector2f GetPosition() { return position; }
    Branch(int, Vector2f);
};

void Branch::grow(float secondsPerDay, float deltaTime){
    length = length + (deltaTime * (growth_rate/secondsPerDay)) * side;
    if(abs(length) > max_length)
        length = max_length * side;
    
}

Branch::Branch(int s, Vector2f pos){
    side = s;
    position = pos;
}
