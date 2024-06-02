#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"

class Collider : public Component
{
public:
    virtual ~Collider() = default;

    virtual bool CheckCollision(Collider &other) const = 0;
};

#endif // COLLIDER_H