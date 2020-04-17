#pragma once

#include "SFML/Graphics/Color.hpp"


class TomatoPlant:public PlantBase
{
public:
    //Constructor
    TomatoPlant(){
        //Sets variables for the tomato plant
        set(10.0, sf::Color(78, 204, 71), 1.0, "Tomato");
    }
};


