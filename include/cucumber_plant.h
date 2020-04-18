#pragma once

#include "SFML/Graphics/Color.hpp"


class CucumberPlant : public PlantBase
{
public:
    //Constructor
    CucumberPlant(){
        //When the class is initiated, it sets all of the values
        width = 7.5;
        color = sf::Color(60, 153, 55);
        growth_rate = 15.0;
        plantName = "Cucumber";
    }

    virtual void PlantGraphicsSpecific() {
    cout << "Tomato Plant PlantGraphics" << endl;
        //If the plant height is taller than where the branch appears
    }
};


