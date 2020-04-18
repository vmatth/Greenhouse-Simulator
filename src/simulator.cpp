#pragma region include
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

#include<plant_base.h>
#include<tomato_plant.h>
#include<cucumber_plant.h>
#include<soil.h>

#include<iostream>
#include<cmath>
#define _USE_MATH_DEFINES
#include<math.h>

using namespace std;
#pragma endregion

//Global variables for the greenhouse simulator
namespace Greenhouse{
    bool running;
    float et; // Elapsed time
    float secondsPerDay = 10;
    float nextPlantPosX = 100; //x-position of the next plant to be added

    vector<PlantBase*> plantsAvailable; //All plant classes
    //Vector of smart pointer allows us to access the derived class of the base :)
    vector<PlantBase*> plants; //Plants in greenhouse
}
using namespace Greenhouse; //Use the namspace, so we don't have to write "Greenhouse::" in front of every variable

Soil soil;

#pragma region Setup Functions
// Add all Plant Classes to the vector: "PlantsAvailable". Manual work
void SetupPlants(){
    TomatoPlant* t = new TomatoPlant;
    plantsAvailable.push_back(t);
    CucumberPlant* c = new CucumberPlant;
    plantsAvailable.push_back(c);
}

#pragma endregion

#pragma region Greenhouse Functions

void Start_Greenhouse(){
    running = true;
}

void Stop_Greenhouse(){
    running = false;
}

void GrowPlants(sf::Time dt){
    for(PlantBase* &p : plants){
        p->grow(secondsPerDay, dt.asSeconds());
        p->PlantGraphics(secondsPerDay, dt.asSeconds());
        //cout << "Plant size: " << p.getHeight() << endl;
    }
}

void Update(sf::Time dt){
    //Delta time = Time since last update
    GrowPlants(dt);
}
#pragma endregion

#pragma region ImGui

void AddPlant(string className){ //Plant class as argument (Ex. TomatoPlant)
    cout << "Added plant: " << className << endl;
    //ass method to create the plant object.
    //Other option was to clone the class from the argument
    //but that was too complicated
    PlantBase* p;
    if(className == "Tomato"){
        p = new TomatoPlant;
    }
    else if(className == "Cucumber"){
        p = new CucumberPlant;
    }
    //Copy this new class into the plants vector
    p->setPosition(sf::Vector2f{nextPlantPosX, 600-50});
    plants.push_back(p);

    nextPlantPosX = nextPlantPosX + 100;
}
/*void AddPlant(PlantBase* &p){ //Plant class as argument (Ex. TomatoPlant)
    cout << "Added plant: " << p->getName() << endl;
    //Copy this new class into the plants vector
    PlantBase* plantCopy = new PlantBase;
    plantCopy->setPosition(sf::Vector2f{nextPlantPosX, 600-50});
    plants.push_back(plantCopy);

    nextPlantPosX = nextPlantPosX + 100;
}*/

void DrawPlants(sf::RenderWindow &window){
    for (PlantBase* &p : plants){
        //cout << "Rendering plant: " << p.getName() << endl;
        sf::RectangleShape stalk{sf::Vector2f{p->getWidth(), -p->getHeight()}};
        stalk.setFillColor(p->getColor());
        stalk.setPosition(p->getPosition());
        window.draw(stalk);
        //Draw additional graphics
        for(sf::RectangleShape &graphic : p->plantRectangleGraphics){
            cout <<"drawing rect graphics" << endl;
            window.draw(graphic);
        }
        //Draw additional graphics
        for(sf::CircleShape &graphic : p->plantCircleGraphics){
            window.draw(graphic);
        }
    }   
}

void DrawSun(sf::RenderWindow &window){
    //Sun
    sf::CircleShape sun{50};
    sun.setFillColor(sf::Color::Yellow);
    //Formula for sun movement
    float y = 500 * sin(2*M_PI/secondsPerDay * et); //Sinuscurve for sun movement.
    sun.setPosition(sf::Vector2f{(float)window.getSize().x / 2 - 50, (float)window.getSize().y - y - 50});
    window.draw(sun);
    //Moon
    sf::CircleShape moon{30};
    moon.setFillColor(sf::Color::White);
    //Formula for moon movement
    y = -500 * sin(2*M_PI/secondsPerDay * et); //Sinuscurve for sun movement.
    moon.setPosition(sf::Vector2f{(float)window.getSize().x / 2 - 30, (float)window.getSize().y - y - 30});
    window.draw(moon);

}

void DrawBackground(sf::RenderWindow &window){
    //Sinus curve for each r, g, b value
    float r_max = 20;
    float g_max = 100;
    float b_max = 200;
    float r = r_max/2 * sin(2*M_PI/secondsPerDay * et) + (r_max/2);
    float g = g_max/2 * sin(2*M_PI/secondsPerDay * et) + (g_max/2);
    float b = b_max/2 * sin(2*M_PI/secondsPerDay * et) + (b_max/2);
    window.clear(sf::Color(r, g, b));
}

void DrawEnvironment(sf::RenderWindow &window){
    //Soil
    sf::RectangleShape soil{sf::Vector2f{800, 50}};
    soil.setPosition(sf::Vector2f{0, 600-50});
    soil.setFillColor(sf::Color(204, 127, 55));
    //Draw
    window.draw(soil);
}

void ImGuiMenus(){
    // Start stop menu
    ImGui::Begin("Start/Stop");
    ImGui::PushItemWidth(50);
    ImGui::InputFloat("Seconds per Day", &secondsPerDay);
    if(!running){
        if(ImGui::Button("Start"))
            Start_Greenhouse();
    }
    else{
        if(ImGui::Button("Stop"))
            Stop_Greenhouse();
    }
    ImGui::Text("Time elapsed: %f", et);
    ImGui::End();

    //Plant picker menu
    ImGui::Begin("Plant picker");
    ImGui::Text("Add Plant:");
    for(PlantBase* &p : plantsAvailable){
        if(ImGui::Button(p->getName().c_str()))
            AddPlant(p->getName());
    }
    ImGui::End();


    //Soil Statistics menu
    ImGui::Begin("Soil values");
    ImGui::Text("Phosfor: %f", soil.getPhosforlevel());
    ImGui::Text("Potassium: %f", soil.getPotassiumlevel());
    ImGui::Text("Nitrate: %f", soil.getNitratelevel());
    ImGui::Text("Soil Moisture Level: %f", soil.getMoisturelevel());
    ImGui::Text("Soil Amount (Liter): %f", soil.getSoilAmount());
    ImGui::End();
}
#pragma endregion

int main(int argc, char const *argv[])
{


    //Setup PlantsAvailable Vector
    SetupPlants();

    // create the window
    static sf::RenderWindow window(sf::VideoMode(800, 600), "Greenhouse Simulator");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    sf::Vector2f screenSize = (sf::Vector2f)window.getSize();

    sf::Clock deltaClock;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // delta time
        if(running){
            sf::Time dt = deltaClock.restart();
            et = et + dt.asSeconds();
            Update(dt);
        //cout << "et: " << et << endl;
        }

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGuiMenus();

        /*ImGui::Begin("Hello, world!");
        if(ImGui::SliderFloat("Length", &stalk_length, 0., 100.)){
            stalk.setSize(sf::Vector2f{5.0, -stalk_length});
        }*/

        // clear the window with defined color
        DrawBackground(window);

        // draw everything here...
        DrawSun(window);
        DrawPlants(window);
        DrawEnvironment(window);
        ImGui::SFML::Render(window);
        // end the current frame
        window.display();

    }

    return 0;
}


