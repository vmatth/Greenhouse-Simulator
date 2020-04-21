#pragma once
#include "SFML/Graphics/Color.hpp"
#include<string>
#include<soil.h>
#include<iostream>
using namespace std;
using namespace sf;

class PlantBase
{
public:
    // Get
    virtual string getName() = 0;

    //Set
    virtual void setPosition(Vector2f) = 0;

    // Functions
    virtual void grow(float, float) = 0;
    virtual void draw(RenderWindow &window) = 0;
   // virtual std::unique_ptr<PlantBase> clone() = 0;
};





