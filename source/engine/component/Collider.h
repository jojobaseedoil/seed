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

    const bool isTrigger;
};

#endif // COLLIDER_H