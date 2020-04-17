#pragma once

#include "SFML/Graphics/Color.hpp"


class CucumberPlant:public PlantBase
{
public:
    //Constructor
    CucumberPlant(){
        //Sets variables for the tomato plant
        set(7.5, sf::Color(60, 153, 55), 1.5, "Cucumber");
    }
};


