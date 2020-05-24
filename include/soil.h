#pragma once

class Soil
{
private:
    double soilQuality = 1; // Value from 0 - 1
    double soil_use_per_plant = 0.05; //Amount of soil quality used per plant in a day
public:

    void fertilize(){
        soilQuality = 1;
    }

    void useNPK(float deltaTime, float secondsPerDay){
        soilQuality = soilQuality - (deltaTime * (soil_use_per_plant/secondsPerDay));
        if(soilQuality < 0){
            soilQuality = 0;
        }
    }

    double getSoilQuality(){
        return soilQuality;
    }
};
