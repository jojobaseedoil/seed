#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "Collider.h"

class BoxCollider : public Collider
{
public:
    BoxCollider(float w, float h, bool isTrigger=false);

    bool CheckCollision(Collider &other) const override;
    void ResolveCollision(Collider &other) override;

    void Update(float deltaTime) override;

private:
    float x, y;
    float w, h;
};

#endif // BOX_COLLIDER_H