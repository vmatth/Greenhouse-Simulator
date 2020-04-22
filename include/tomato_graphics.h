#pragma once

#include "SFML/Graphics/Color.hpp"
#include <iostream>
#include <tomato_plant.h>
#include <branch.h>

using namespace sf;

class TomatoGraphics
{
private:
    Color color = Color(78, 204, 71);
    Color fruitColor = Color(235, 70, 50);
public:
    void draw(RenderWindow &window, float, float, Vector2f, vector<Branch>);
};

void TomatoGraphics::draw(RenderWindow &window, float width, float height, Vector2f position, vector<Branch> branches){
    //Draw stalk
    RectangleShape stalk{Vector2f{width, -height}};
    stalk.setFillColor(color);
    stalk.setPosition(position);
    window.draw(stalk);

    //Draw Branches
    for(Branch &b : branches){
        RectangleShape branch{Vector2f(b.GetLength(), b.GetWidth())};
        branch.setFillColor(color);
        branch.setPosition(b.GetPosition()); 
        window.draw(branch);
        //Draw fruits
        if(b.GetFruit().GetRound()){
            CircleShape fruit{b.GetFruit().GetSize()}; 
            fruit.setFillColor(fruitColor);
            fruit.setPosition(b.GetFruit().GetPosition()); 
            window.draw(fruit);
        }
        else {
            RectangleShape fruit{Vector2f(b.GetFruit().GetWidth(), b.GetFruit().GetSize())};
            fruit.setFillColor(fruitColor);
            fruit.setPosition(b.GetFruit().GetPosition()); 
            window.draw(fruit);
        }

 
        
    }

}

