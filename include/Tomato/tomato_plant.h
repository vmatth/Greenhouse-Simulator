#pragma once

#include <iostream>
#include <tomato_graphics.h>
#include <tomato_grower.h>

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
    TomatoGrower grower;
public:
    // Get
    string getName() override { return plantName; }

    //Set
    void setPosition(Vector2f pos) override { position = pos; }

    // Functions
    void grow(float, float) override;
    void draw(RenderWindow &window) override;

};

void TomatoPlant::grow(float secondsPerDay, float deltaTime){
    height = height + (deltaTime * (growth_rate/secondsPerDay));
    if(height > max_height) height = max_height;
    grower.grow(secondsPerDay, deltaTime, height, width, position);
}

void TomatoPlant::draw(RenderWindow &window){
    graphics.draw(window, width, height, position, grower.GetBranches());
}
















/*#pragma once


#include <iostream>
#include <tomato_branch.h>
#include "SFML/Graphics/Color.hpp"*/

/*
class TomatoPlant : public PlantBase
{
private:
    //All plant variables in base class
    string plantName = "Plant";

    float height{10.0};
    float width{1.0};
    float max_height{40.0};
    int num_fruits{0};
    double growth_rate = 0; //Height growth per day

public:
    //Constructor
    TomatoPlant();

    // Shows graphic for the tomato plant (branches, fruits, etc)
    void PlantGraphicsSpecific(float, float) override;

    void AddBranch();

    void grow(float, float);

    void GrowBranch(float, float);

    vector<TomatoBranch> branches; //Vector of the branches
}

//Grows branches in the branches vector
//Uses secondsPerDay and seconds as arguments
void TomatoPlant::GrowBranch(float secondsPerDay, float deltaTime){
    if(branches.size() == 0) return;
    for(TomatoBranch &b : branches){
        b.grow(secondsPerDay, deltaTime);
        plantRectangleGraphics[b.getIndex()].setSize(sf::Vector2f(b.getLength(), b.getWidth()));
    }
}


// Define the PlantGraphics function
void TomatoPlant::PlantGraphicsSpecific(float spd, float s){
    //cout << "Tomato Plant PlantGraphics" << endl;
    AddBranch();
    //Grow branches that have already appeared
    GrowBranch(spd, s);
}
void TomatoPlant::grow(float secondsPerDay, float deltaTime){
    height = height + (deltaTime * (growth_rate/secondsPerDay));
    if(height > max_height)
        height = max_height;
}

//Constructor
TomatoPlant::TomatoPlant(){
    //When the class is initiated, it sets all of the values
    width = 10.0;
    color = sf::Color(78, 204, 71);
    growth_rate = 10.0; 
    max_height = 100;
    plantName = "Tomato";
    grow_right = rand() & 1;

}
*/


