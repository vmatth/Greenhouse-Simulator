#pragma once
#include "SFML/Graphics/Color.hpp"
#include<string>
#include<soil.h>
#include<iostream>
using namespace std;

class PlantBase
{
protected:
    //All plant variables in base class
    string plantName = "Plant";

    float height{10.0};
    float width{1.0};
    float max_height{40.0};
    int num_fruits{0};
    double growth_rate = 0; //Height growth per day

    //ImGui Variables
    sf::Color color;
    sf::Vector2f position; //Planted position
public:
    // Get variables
    float getHeight() { return height; }
    float getWidth() { return width; }
    int getNumFruits() { return num_fruits; }
    float getMaxHeight() { return max_height;}
    sf::Color getColor(){ return color; }
    string getName(){ return plantName; }
    sf::Vector2f getPosition(){ return position; }

    // Set variables
    void setHeight(float h) { height = h; }
    void setMaxHeight(float mh) { max_height = mh; }
    void setPosition(sf::Vector2f p){ position = p; }

    // Functions
    void grow(float, float);

    // Plant Graphics checks when to create additional graphics such as branches or fruits
    // This function is called on the base, and then calls the derived functions
    void PlantGraphics(float, float);

    // Shows the graphics for a plant
    // Each plant has their own function that overrides this one
    virtual void PlantGraphicsSpecific(float, float);

    //Vector containing all of the additional plant graphics
    //Such as branches & fruits. (Not the stalk)
    vector<sf::RectangleShape> plantRectangleGraphics;
    vector<sf::CircleShape> plantCircleGraphics;
};

//Define functions

//Grow function. Uses secondsPerDay as argument, and seconds since last update
//Growth_rate / secondsPerDay to calculate how much to grow each update
void PlantBase::grow(float secondsPerDay, float deltaTime){
    height = height + (deltaTime * (growth_rate/secondsPerDay));
    if(height > max_height)
        height = max_height;
}

void PlantBase::PlantGraphics(float spd, float s){
    //cout <<"PlantBase Graphics" << endl;
    this->PlantGraphicsSpecific(spd, s);
}

void PlantBase::PlantGraphicsSpecific(float, float){
    //Should never get called since it gets overriden by derived classes
    cout <<"If you see this something is wrong lmao"<<endl;
}




