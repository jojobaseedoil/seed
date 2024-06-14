#include "Collider.h"

#include "../entity/GameObject.h"
#include "../system/collision/CollisionSystem.h"

Collider::Collider(Layer layer, bool isTrigger):
    layer          (layer),
    isTrigger      (isTrigger),
    mCurrCollision (-1)
{
    CollisionSystem *csys = CollisionSystem::GetInstance();
    csys->Insert(layer, this);
}

Collider::~Collider()
{
    CollisionSystem *csys = CollisionSystem::GetInstance();
    csys->Remove(layer, this);
}

bool Collider::isInside(int tag) const
{
    return mCurrCollision == tag;
}

void Collider::SetInside(int tag)
{
    mCurrCollision = tag;
}