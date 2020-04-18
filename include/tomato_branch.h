#pragma once

#include "SFML/Graphics/Color.hpp"
#include<cmath>
using namespace std;

class TomatoBranch{ //Branch class, contains information about a specific branch
private:
    float length = 0.0; //Branch length
    const float width = 5.0; //Branch width
    float max_length = 25.0;
    const float growth_rate = 5.0; //Length per day
    int side = 1; //Left = -1, Right = 1
    int index = 0; //Branch index of the plantRectangleGraphics vector
    sf::Vector2f position; //Branch position
    sf::Color color = sf::Color(78, 204, 71);

public:
    float getLength(){return length;}
    float getWidth(){return width;}
    int getIndex(){return index; }
    sf::Color getColor(){return color;}

    //Constructor. Setup right and index values when creating the class
    TomatoBranch(int s, sf::Vector2f pos, int i){
        side = s;
        position = pos;
        index = i;
    }

    //Growfunction
    void grow(float, float);
};

void TomatoBranch::grow(float secondsPerDay, float seconds){
    length = length + (seconds * (growth_rate/secondsPerDay)) * side;
    if(abs(length) > max_length)
        length = max_length * side;

}