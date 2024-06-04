#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"

class Collider : public Component
{
public:
    Collider(bool isTrigger=false);
    virtual ~Collider() = default;

    virtual bool CheckCollision(Collider &other) const = 0;
    virtual void ResolveCollision(Collider &other) = 0;

public:
    const bool isTrigger;
    bool isInside;
};

#endif // COLLIDER_H