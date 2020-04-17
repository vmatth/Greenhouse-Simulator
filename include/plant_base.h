#pragma once
#include "SFML/Graphics/Color.hpp"
#include<string>
using namespace std;

class PlantBase
{
private:
    string plantName = "Plant";
    float height{10.0};
    float width{1.0};

    int num_fruits{0};

    double growth_rate = 0; //Height growth per second

    //ImGui Variables
    sf::Color color;
    sf::Vector2f position; //Planted position
public:
    #pragma region Get
    float getHeight() { return height; }
    float getWidth() { return width; }
    int getNumFruits() { return num_fruits; }
    sf::Color getColor(){ return color; }
    string getName(){ return plantName; }
    sf::Vector2f getPosition(){ return position; }
    #pragma endregion

    #pragma region Set
    void setHeight(float h) { height = h; }
    void setWidth(float w) {width = w; }
    void setColor(sf::Color c){ color = c; }
    void setGrowthRate(double g){ growth_rate = g; }
    void setName(string n){ plantName = n; }
    void setPosition(sf::Vector2f p){ position = p; }
    #pragma endregion

    //Set variables (When initiating a class, set their respective variables)
    void set(float w, sf::Color c, double g, string n){
        setWidth(w);
        setColor(c);
        setGrowthRate(g);
        setName(n);
    }

    void grow(float seconds){
        height = height + (seconds * growth_rate);
    }
};


