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
    float max_height = 150.0;
    int num_fruits = 0;
    double growth_rate = 15.0; //Height growth per day

    Vector2f position; //Planted position
    CucumberGraphics graphics;
    BranchGrower grower;
public:
    // Get
    string getName() override { return plantName; }

    //Set
    void setPosition(Vector2f pos) override { position = pos; }

    // Functions
    void grow(float, float) override;
    void draw(RenderWindow &window) override;

    CucumberPlant();
};

void CucumberPlant::grow(float secondsPerDay, float deltaTime){
    height = height + (deltaTime * (growth_rate/secondsPerDay));
    if(height > max_height) height = max_height;
    grower.grow(secondsPerDay, deltaTime, height, width, position);
}

void CucumberPlant::draw(RenderWindow &window){
    graphics.draw(window, width, height, position, grower.GetBranches());
}

CucumberPlant::CucumberPlant(){
    //Setup values for how tomato growth should be
    //Values for grower, branch and fruit classes.
    //Setup branch values for how tomato branches should grow
    grower.Setup(35, 25, 25, //height_for_growth, next_branch_y, distance_between_branches
                4, 10, 4, //branch_width, branch_max_length, branch_growth_Rate
                8, 20, 8, false); //fruit width, fruit_max_size, fruit_growth_rate, fruit_round
}







