#pragma once

#include "SFML/Graphics/Color.hpp"
#include <iostream>
#include <cucumber_plant.h>

using namespace sf;

class CucumberGraphics
{
private:
    Color color = Color(60, 150, 50);
public:
    void draw(RenderWindow &window, float, float, Vector2f);
};

void CucumberGraphics::draw(RenderWindow &window, float width, float height, Vector2f position){
    RectangleShape stalk{Vector2f{width, -height}};
    stalk.setFillColor(color);
    stalk.setPosition(position);
    window.draw(stalk);
}

