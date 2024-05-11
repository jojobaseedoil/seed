#pragma once

#include "Math.h"

struct Transform{

    explicit Transform(
        const Vector2 &p = Vector2(0.0f, 0.0f),
        const Vector2 &r = Vector2(0.0f, 0.0f),
        const Vector2 &s = Vector2(1.0f, 1.0f)
    ) :
        position (p),
        rotation (r),
        scale    (s)
    {

    }

    Vector2 position;
    Vector2 rotation;
    Vector2 scale;
};