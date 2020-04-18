#pragma once


#include <iostream>
#include <tomato_branch.h>
#include "SFML/Graphics/Color.hpp"


class TomatoPlant : public PlantBase
{
private:
    bool grow_branches = false; //Turns true when a certain height is met
    const float height_for_growth = 30; //Plant height when branches can start growing
    float next_branch_y = 20; //The y-position where the next branch will appear
    const float distance_between_each_branch = 10; //y distance between each branch
    bool grow_right = true; //Determines which side the branch will grow on. false = left
public:
    //Constructor
    TomatoPlant();

    // Shows graphic for the tomato plant (branches, fruits, etc)
    void PlantGraphicsSpecific(float, float) override;

    void AddBranch();

    void GrowBranch(float, float);

    vector<TomatoBranch> branches; //Vector of the branches
};

void TomatoPlant::AddBranch(){
    //Check for plant height
    if(height > height_for_growth)
        grow_branches = true;
    //If can grow branches
    if(grow_branches){
        if(height > next_branch_y + distance_between_each_branch){
            cout << "Add branch!" << endl;
            //Make shape
            sf::RectangleShape b{sf::Vector2f{15.0, 5.0}};
            sf::Vector2f branchPos = position - sf::Vector2f(0, next_branch_y);
            if(grow_right)  branchPos += sf::Vector2f(width, 0); //If branch is on right, offset the branch
            b.setPosition(branchPos); 
            //Push to graphics vector. The branch class changes the graphic when growing
            
            int side = 1; if (grow_right == false) side = -1;
            //Create branch class with values from this class
            TomatoBranch tomatoBranch(side, 
                                      branchPos,
                                      plantRectangleGraphics.size());
            branches.push_back(tomatoBranch);

            b.setFillColor(tomatoBranch.getColor());
            plantRectangleGraphics.push_back(b);

            //Setup variables for next branch
            grow_right = !grow_right; //Flip bool
            next_branch_y = next_branch_y + distance_between_each_branch;
        }
    }
}

//Grows branches in the branches vector
//Uses secondsPerDay and seconds as arguments
void TomatoPlant::GrowBranch(float secondsPerDay, float seconds){
    if(branches.size() == 0) return;
    for(TomatoBranch &b : branches){
        b.grow(secondsPerDay, seconds);
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



