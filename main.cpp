#include "json.h"
#include "entity.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std::chrono;

Entity* CreateDrone() {
    std::ifstream file;
    file.open("umn.json");

    picojson::value v;
    file >> v;

    JsonArray arr = JsonValue(v);
    JsonObject command = arr[0];
    JsonObject drone = command["params"];

    return new Entity(drone);
}

int main() {

    std::ifstream file;
    file.open("umn.json");

    picojson::value v;
    file >> v;

    JsonArray arr = JsonValue(v);
    JsonObject command = arr[0];
    JsonObject drone = command["params"];
    double speed = drone["speed"];
    std::string name = drone["name"];

    std::cout << "speed: " << speed << '\n' << "name: " << name << std::endl;

    JsonObject obj;
    obj["string"] = "hello";
    obj["number"] = 9.5;
//    obj["array"] = JsonArray();
    std::cout << "obj: " << obj << std::endl;

    Entity* entity = CreateDrone();

    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(milliseconds(100) );
        entity->Update(0.1);
        auto details = entity->GetDetails();
        std::cout << details << std::endl;
    }

    delete entity;

    return 0;
}