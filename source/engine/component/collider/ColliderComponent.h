#pragma once

#include <vector>

#include "../Component.h"

class ColliderComponent : public Component
{
public:
    ColliderComponent(GameObject *owner);

    /* check if its an intersection between two colliders */
    virtual bool intersect(ColliderComponent *other) = 0;

    /* */
    void detectCollision(std::vector<ColliderComponent*> &colliders);
};