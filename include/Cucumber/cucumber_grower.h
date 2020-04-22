#pragma once

#include "SFML/Graphics/Color.hpp"
#include <cmath>
#include <cucumber_branch.h>

using namespace std;
using namespace sf;

class CucumberGrower{ //Branch class, contains function to add branches to a plant
private:
    //Values for when to add a branch
    bool grow_branches = false; //Turns true when a certain height is met
    float height_for_growth = 40; //Plant height when branches can start growing
    float next_branch_y = 25; //The y-position where the next branch will appear
    float distance_between_each_branch = 25; //y distance between each branch
    bool grow_right = true; //Determines which side the branch will grow on. false = left
  
public:
    void grow(float, float, float, float,Vector2f);
    void AddBranch(float, float, Vector2f);
    void GrowBranches(float, float);
    //void AddFruit(Branch);
    vector<CucumberBranch> GetBranches() { return branches; }

    void Setup();

    vector<CucumberBranch> branches;
};

void CucumberGrower::AddBranch(float height, float width, Vector2f position){
    //Check for plant height
    if(height > height_for_growth)
        grow_branches = true;
    //If can grow branches
    if(grow_branches){
        if(height > next_branch_y + distance_between_each_branch){

            //Calculate position for new branch
            Vector2f branchPos = position - Vector2f(0, next_branch_y);
            if(grow_right) branchPos += sf::Vector2f(width, 0); //If branch is on right, offset the branch
            
            int side = 1; if (grow_right == false) side = -1;

            //Create branch and add to vector
            CucumberBranch branch(side, branchPos);
            branches.push_back(branch);

            //Setup variables for next branch
            grow_right = !grow_right; //Flip bool
            next_branch_y = next_branch_y + distance_between_each_branch;
        }
    }
}

void CucumberGrower::GrowBranches(float secondsPerDay, float deltaTime){
    for(CucumberBranch &b : branches){
        b.grow(secondsPerDay, deltaTime);
    }
}

void CucumberGrower::grow(float secondsPerDay, float deltaTime, float height, float width, Vector2f position){
    AddBranch(height, width, position);
    GrowBranches(secondsPerDay, deltaTime);
}

//void TomatoBranch::AddFruit(TomatoBranch branch){
    
//}

void CucumberGrower::Setup(){
    grow_right = rand() & 1; //Random side for first branch
}
