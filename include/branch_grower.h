#pragma once

#include "SFML/Graphics/Color.hpp"
#include <cmath>
#include <branch.h>

using namespace std;
using namespace sf;

class BranchGrower{ //Branch class, contains function to add branches to a plant
private:
    //Each plant uses the same BranchGrower class
    //But in the Setup() function, different values are set unique for each class

    //Values for when to add a branch
    bool grow_branches = false; //Turns true when a certain height is met
    float height_for_growth = 30; //Plant height when branches can start growing
    float next_branch_y = 20; //The y-position where the next branch will appear
    float distance_between_each_branch = 10; //y distance between each branch
    bool grow_right = true; //Determines which side the branch will grow on. false = left

    //Branch values
    float branch_width, branch_max_length, branch_growth_rate = 0;

    //Fruit values
    float fruit_width, fruit_max_size, fruit_growth_rate = 0;
    bool fruit_round;
  
public:
    void grow(float, float, float, float,Vector2f);
    void AddBranch(float, float, Vector2f);
    void GrowBranches(float, float);
    //void AddFruit(Branch);
    vector<Branch> GetBranches() { return branches; }

    void Setup(float, float, float, float, float, float, float, float, float, bool);

    vector<Branch> branches;
};

void BranchGrower::AddBranch(float height, float width, Vector2f position){
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
            Branch branch(branch_width, branch_max_length, branch_growth_rate, side, branchPos, fruit_width, fruit_max_size, fruit_growth_rate, fruit_round);
            branches.push_back(branch);

            //Setup variables for next branch
            grow_right = !grow_right; //Flip bool
            next_branch_y = next_branch_y + distance_between_each_branch;
        }
    }
}

void BranchGrower::GrowBranches(float secondsPerDay, float deltaTime){
    for(Branch &b : branches){
        b.grow(secondsPerDay, deltaTime);
    }
}

void BranchGrower::grow(float secondsPerDay, float deltaTime, float height, float width, Vector2f position){
    AddBranch(height, width, position);
    GrowBranches(secondsPerDay, deltaTime);
}

//void TomatoBranch::AddFruit(TomatoBranch branch){
    
//}

void BranchGrower::Setup(float Height_for_growth, float Next_branch_y, float Distance_between_each_branch,
                         float Branch_width, float Branch_max_length, float Branch_growth_rate,
                         float Fruit_width, float Fruit_max_size, float Fruit_growth_rate, bool Fruit_round){
    height_for_growth = Height_for_growth;
    next_branch_y = Next_branch_y;
    distance_between_each_branch = Distance_between_each_branch;

    branch_width = Branch_width;
    branch_max_length = Branch_max_length;
    branch_growth_rate = Branch_growth_rate;
    grow_right = rand() & 1; //Random side for first branch

    fruit_width = Fruit_width;
    fruit_max_size = Fruit_max_size;
    fruit_growth_rate = Fruit_growth_rate;
    fruit_round = Fruit_round;
}
