#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"

enum Layer
{
    Instances,
    Background,
    Wall,
    Player,
    Box
};

class Collider : public Component
{
public:
    Collider(Layer layer=Layer::Instances, bool isTrigger=false);
    virtual ~Collider();

    virtual bool CheckCollision(Collider &other) const = 0;
    virtual void ResolveCollision(Collider &other) = 0;

    bool isInside(int tag) const;
    void SetInside(int tag);

public:
    const bool isTrigger;
    const Layer layer;

private:
    int mCurrCollision;
};

#endif // COLLIDER_H