#pragma once

#include "ColliderComponent.h"
#include "../../utils/Math.h"

struct Box
{
    float x, y;
    float w, h;
};

class AABB : public ColliderComponent
{
public:
    AABB(GameObject *owner, Observer *obs, float w=32.0f, float h=32.0f);

    bool intersect(GameObject *other) override;
    void resolve(GameObject *other) override;

    /* important points of the AABB */
    Vector2 min() const;
    Vector2 max() const;
    Vector2 center() const;

private:
    Box mAABB;
};