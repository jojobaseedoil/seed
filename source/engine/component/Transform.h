#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

#include "../utils/Math.h"

class Transform : public Component
{
public:
    Vector2 position = Vector2(0,0);
    Vector2 rotation = Vector2(0,0);
    Vector2 scale    = Vector2(1,1);
};

#endif // TRANSFORM_H