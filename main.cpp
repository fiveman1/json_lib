#include "json.h"

#include <iostream>
#include <fstream>

int main() {

    std::ifstream json;
    json.open("umn.json");

    picojson::value v;
    json >> v;

    JsonArray arr = JsonValue(v);
    JsonObject command = arr[0];
    JsonObject drone = command["params"];
    double speed = drone["speed"];
    std::string name = drone["name"];

    std::cout << "speed: " << speed << '\n' << "name: " << name << std::endl;


    JsonObject obj;
    obj["mother"] = "the j";
    std::cout << "val: " << obj << std::endl;

    return 0;
}