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
using namespace sf;

#pragma endregion

//Global variables for the greenhouse simulator
namespace Greenhouse{
    bool running;
    float et; // Elapsed time
    int days = 0;
    float secondsPerDay = 10;
    float nextPlantPosX = 100.0; //x-position of the next plant to be added

    //Defines a vector of pointers to all plants available in the greenhouse
    vector<unique_ptr<PlantBase>> plantsAvailable; //All plant classes
    //Vector of pointer to all plants added to the greenhouse
    vector<unique_ptr<PlantBase>> plants; //Plants in greenhouse
}
using namespace Greenhouse; //Use the namespace, so we don't have to write "Greenhouse::" in front of every variable

Soil soil;

#pragma region Setup Functions
// Add all Plant Classes to the vector: "PlantsAvailable".
void SetupPlants(){
    plantsAvailable.push_back(make_unique<TomatoPlant>());
    plantsAvailable.push_back(make_unique<CucumberPlant>());
}

#pragma endregion

#pragma region Greenhouse Functions

void GrowPlants(Time dt){
    for(unique_ptr<PlantBase> &p : plants){
        p->grow(secondsPerDay, dt.asSeconds());
    }
}

void Update(Time dt){
    //Delta time = Time since last update
    GrowPlants(dt);
}
#pragma endregion

#pragma region ImGui

// Add a plant to the greenhouse
void AddPlant(string className){
    cout << "Added plant: " << className << endl;

    if(className == "Tomato"){
        plants.push_back(make_unique<TomatoPlant>());
    }
    else if(className == "Cucumber"){
        plants.push_back(make_unique<CucumberPlant>());
    }

    plants[plants.size()-1]->setPosition(Vector2f(nextPlantPosX, 550));
    nextPlantPosX = nextPlantPosX + 100;
}
void DrawPlants(RenderWindow &window){
    for (unique_ptr<PlantBase> &p : plants){
        p->draw(window);
    }   
}

void DrawSun(RenderWindow &window){
    //Sun
    CircleShape sun{50};
    sun.setFillColor(Color::Yellow);
    //Formula for sun movement
    float y = 500 * sin(2*M_PI/secondsPerDay * et); //Sinuscurve for sun movement.
    sun.setPosition(Vector2f{(float)window.getSize().x / 2 - 50, (float)window.getSize().y - y - 50});
    window.draw(sun);
    //Moon
    CircleShape moon{30};
    moon.setFillColor(Color::White);
    //Formula for moon movement
    y = -500 * sin(2*M_PI/secondsPerDay * et); //Sinuscurve for sun movement.
    moon.setPosition(Vector2f{(float)window.getSize().x / 2 - 30, (float)window.getSize().y - y - 30});
    window.draw(moon);

}

void DrawBackground(RenderWindow &window){
    //Sinus curve for each r, g, b value
    float r_max = 20;
    float g_max = 100;
    float b_max = 200;
    float r = r_max/2 * sin(2*M_PI/secondsPerDay * et) + (r_max/2);
    float g = g_max/2 * sin(2*M_PI/secondsPerDay * et) + (g_max/2);
    float b = b_max/2 * sin(2*M_PI/secondsPerDay * et) + (b_max/2);
    window.clear(Color(r, g, b));
}

void DrawEnvironment(RenderWindow &window){
    //Soil
    RectangleShape soil{Vector2f{800, 50}};
    soil.setPosition(Vector2f{0, 600-50});
    soil.setFillColor(Color(204, 127, 55));
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
            running = true;
    }
    else{
        if(ImGui::Button("Stop"))
            running = false;
    }
    ImGui::Text("Time elapsed: %f", et);
    //ImGui::Text("Days passed: %d", days);
    ImGui::End();

    //Plant picker menu
    ImGui::Begin("Plant picker");
    ImGui::Text("Add Plant:");
    for(unique_ptr<PlantBase> &p : plantsAvailable){
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
    static RenderWindow window(VideoMode(800, 600), "Greenhouse Simulator");
    window.setFramerateLimit(30);
    ImGui::SFML::Init(window);
    Vector2f screenSize = (Vector2f)window.getSize();

    Clock deltaClock;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // delta time
        if(running){
            Time dt = deltaClock.restart();
            et = et + dt.asSeconds();
            Update(dt);
        }

        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGuiMenus();

        // Draw stuff
        DrawBackground(window);
        DrawSun(window);
        DrawPlants(window);
        DrawEnvironment(window);
        ImGui::SFML::Render(window);
        // end the current frame
        window.display();

    }

    return 0;
}


