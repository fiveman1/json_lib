#include "json.h"

#include <iostream>
#include <fstream>

int main() {

    std::ifstream json;
    json.open("umn.json");

    picojson::value v;
    json >> v;
    picojson::array arr = v.get<picojson::array>();
    JsonValue first = arr[0];
    JsonObject command = first;
    JsonObject drone = command["params"];
    double speed = drone["speed"];
    std::string name = drone["name"];

    std::cout << "speed: " << speed << '\n' << "name: " << name << std::endl;


    JsonObject obj;
    obj["mother"] = "the j";
    JsonValue val(obj);
    std::cout << "val: " << val << std::endl;

    return 0;
}