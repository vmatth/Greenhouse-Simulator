#pragma once

#include "SFML/Graphics.hpp"
using namespace sf;
//#include <tomato_branch.h>

class Fruit{//7.5 3.75
private:
    float size = 0;
    float max_size = 0;
    float width = 0;
    float growth_rate = 0; 

    bool round = false; //Round or square fruit

    Vector2f position;
public:

    void grow(float, float);
    void SetPosition(Vector2f, float);
    void Setup(float, float, float, bool);

    float GetSize() { return size; }
    float GetWidth() { return width; }
    Vector2f GetPosition() { return position; }
    bool GetRound() { return round; }

};

void Fruit::grow(float secondsPerDay, float deltaTime){
    size = size + (deltaTime * (growth_rate/secondsPerDay));
    if(size > max_size) size = max_size;
    cout << "Fruit size: " << size << endl;
}

void Fruit::SetPosition(Vector2f branch_pos, float branch_length){
    if(round)
        position = branch_pos + Vector2f(branch_length - size, 0);
    else
        position = branch_pos + Vector2f(branch_length - (width / 2), 0);
}

void Fruit::Setup(float Max_size, float Width, float Growth_rate, bool Round){
    max_size = Max_size;
    width = Width;
    growth_rate = Growth_rate;
    round = Round;
}

