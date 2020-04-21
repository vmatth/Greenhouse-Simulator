#pragma once

#include <iostream>
#include <cucumber_graphics.h>

using namespace sf;


class CucumberPlant : public PlantBase
{
private:
    //All plant variables in base class
    string plantName = "Cucumber";

    float height = 10.0;
    float width = 7.5;
    float max_height = 70.0;
    int num_fruits = 0;
    double growth_rate = 15.0; //Height growth per day

    Vector2f position; //Planted position
    CucumberGraphics graphics;
public:
    // Get
    string getName() override { return plantName; }

    //Set
    void setPosition(Vector2f pos) override { position = pos; }

    // Functions
    void grow(float, float) override;
    void draw(RenderWindow &window) override;
};

void CucumberPlant::grow(float secondsPerDay, float deltaTime){
    height = height + (deltaTime * (growth_rate/secondsPerDay));
    if(height > max_height)
        height = max_height;
}

void CucumberPlant::draw(RenderWindow &window){
    graphics.draw(window, width, height, position);
}









