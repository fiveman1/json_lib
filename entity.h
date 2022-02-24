#ifndef ENTITY_H
#define ENTITY_H

#include "json.h"

class Entity {

public:

    explicit Entity(JsonObject obj) : details(std::move(obj)) {}

    JsonObject GetDetails() const { return details; }

    void Update(double dt) {}

protected:
    JsonObject details;
};

#endif //ENTITY_H
