#pragma once

class Soil
{
private:
    double Phosfor = 0.20; //Percantage of soil
    double Potassium = 0.20; //Percentage of soil
    double Nitrate = 0.20; //Percentage of soil
    double soil_moisturelevel = 0.50; //Percentage of soil
    double soil_amount = 1; //Amount of liter soil
public:
    void add_soil(double amount){soil_amount += amount;}
    void water_plant(int litres_of_water){soil_moisturelevel += litres_of_water/soil_amount;}
    void Fertilize_NPK(int n_amount, int p_amount, int k_amount){Phosfor += p_amount; Nitrate += n_amount; Potassium += k_amount;}
    double getNitratelevel(){return Nitrate;}
    double getPotassiumlevel() {return Potassium;}
    double getPhosforlevel() {return Phosfor;}
    double getMoisturelevel() {return soil_moisturelevel;}
    double getSoilAmount() { return soil_amount; }
    void useN(){Nitrate -= 0.05;}
    void useP(){Phosfor -= 0.05;}
    void useK(){Potassium -= 0.05;}

};
