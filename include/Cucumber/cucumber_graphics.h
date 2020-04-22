#pragma once

#include "SFML/Graphics/Color.hpp"
#include <iostream>
#include <cucumber_plant.h>
#include <cucumber_branch.h>

using namespace sf;

class CucumberGraphics
{
private:
    Color color = Color(70, 200, 70);
    Color fruitColor = Color(17, 112, 25);
public:
    void draw(RenderWindow &window, float, float, Vector2f, vector<CucumberBranch>);
};

void CucumberGraphics::draw(RenderWindow &window, float width, float height, Vector2f position, vector<CucumberBranch> branches){
    RectangleShape stalk{Vector2f{width, -height}};
    stalk.setFillColor(color);
    stalk.setPosition(position);
    window.draw(stalk);

    //Draw Branches
    for(CucumberBranch &b : branches){
        RectangleShape branch{Vector2f(b.GetLength(), b.GetWidth())};
        branch.setFillColor(color);
        branch.setPosition(b.GetPosition()); 
        window.draw(branch);
        //Draw fruits
        RectangleShape fruit{Vector2f(b.GetFruit().GetWidth(), b.GetFruit().GetSize())};
        fruit.setFillColor(fruitColor);
        fruit.setPosition(b.GetFruit().GetPosition()); 
        window.draw(fruit);      
    }
}

