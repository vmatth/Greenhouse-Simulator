#pragma once

#include <fruit.h>
#include <leaves.h>

class Branch
{
private:
    float length = 0.0;
    float width = 5.0;
    float max_length = 25.0;
    float growth_rate = 5.0; //Length per day
    int side = 1; //Left = -1, Right = 1
    Vector2f position;
    
    Fruit fruit;
    Leaves leaves;
public:
    Branch(float, float, float, int, Vector2f, float, float, float, bool);

    void grow(float, float);
    float GetWidth() { return width; }
    float GetLength() { return length; }
    Vector2f GetPosition() { return position; }
    Fruit GetFruit() { return fruit; }
};


void Branch::grow(float secondsPerDay, float deltaTime){
    length = length + (deltaTime * (growth_rate/secondsPerDay)) * side;
    if(abs(length) > max_length){
        length = max_length * side;  
        fruit.grow(secondsPerDay, deltaTime);
        fruit.SetPosition(position, length);
        leaves.grow(secondsPerDay, deltaTime);
    }
}

Branch::Branch(float Width, float Max_length, float Growth_rate, int s, Vector2f pos, float fruit_width, float fruit_max_size, float fruit_growth_rate, bool round){
    width = Width;
    max_length = Max_length;
    growth_rate = Growth_rate;
    side = s;
    position = pos;

    fruit.Setup(fruit_max_size, fruit_width, fruit_growth_rate, round);
}

