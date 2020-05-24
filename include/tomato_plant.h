#pragma once

#include <iostream>
#include <tomato_graphics.h>
#include <branch_grower.h>

using namespace sf;


class TomatoPlant : public PlantBase
{
private:
    //All plant variables
    string plantName = "Tomato";

    float height = 10.0;
    float width = 10.0;
    float max_height = 100.0;
    int num_fruits = 0;
    double growth_rate = 10.0; //Height growth per day

    //Variables for the branches

    Vector2f position; //Planted position
    TomatoGraphics graphics;
    BranchGrower grower;
public:
    // Get
    string getName() override { return plantName; }

    //Set
    void setPosition(Vector2f pos) override { position = pos; }

    // Functions
    void grow(float, float, float) override;
    void draw(RenderWindow &window) override;

    TomatoPlant();
};

void TomatoPlant::grow(float secondsPerDay, float deltaTime, float soilQuality){
    height = height + (deltaTime * (growth_rate/secondsPerDay) * soilQuality);
    if(height > max_height) height = max_height;
    grower.grow(secondsPerDay, deltaTime, height, width, position);
}

void TomatoPlant::draw(RenderWindow &window){
    graphics.draw(window, width, height, position, grower.GetBranches());
}

TomatoPlant::TomatoPlant(){
    //Setup values for how tomato growth should be
    //Values for grower, branch and fruit classes.
    //Setup branch values for how tomato branches should grow
    grower.Setup(30, 20, 10, //height_for_growth, next_branch_y, distance_between_branches
                5, 25, 5, //branch_width, branch_max_length, branch_growth_Rate
                0, 7.5, 3.5, true); //fruit width, fruit_max_size, fruit_growth_rate, fruit_round
}


