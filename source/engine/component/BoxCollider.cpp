#include "BoxCollider.h"

#include "../entity/GameObject.h"
#include "RigidBody.h"

#include <SDL2/SDL_log.h>

BoxCollider::BoxCollider(float w, float h, Layer layer, bool isTrigger):
    Collider (layer, isTrigger),
    x        (0.0f),
    y        (0.0f),
    w        (w), 
    h        (h)
{

}

bool BoxCollider::CheckCollision(Collider &other) const
{
    const BoxCollider *box = dynamic_cast<const BoxCollider*>(&other);

    if(box)
    {        
        return (
            this->x < box->x  + box->w  &&
            this->y < box->y  + box->h  &&
            box->x  < this->x + this->w &&
            box->y  < this->y + this->h 
        );
    }

    return false;
}

void BoxCollider::ResolveCollision(Collider &other)
{
    BoxCollider *box = dynamic_cast<BoxCollider*>(&other);

    if(!box || box->isTrigger)
    {
        return;
    }

    const float epsilon = 0.001f; // overlap correction

    // Calculates the overlaps in all axis
    float overlapX1 = x + w - box->x;
    float overlapX2 = box->x + box->w - x;
    float overlapY1 = y + h - box->y;
    float overlapY2 = box->y + box->h - y;

    // Choose the min overlap to separe the boxes
    if(std::min(overlapX1, overlapX2) < std::min(overlapY1, overlapY2)) 
    {
        x += overlapX1 < overlapX2 ? -(overlapX1 > epsilon ? overlapX1 - epsilon : 0.0f) : overlapX2;
    } 
    else 
    {
        y += overlapY1 < overlapY2 ? -(overlapY1 > epsilon ? overlapY1 - epsilon : 0.0f) : overlapY2; 
    }

    // Update GameObject position
    if(mGameObject) 
    {
        mGameObject->transform.position.x = x;
        mGameObject->transform.position.y = y;
    }
}

void BoxCollider::Update(float deltaTime)
{
    if(mGameObject)
    {
        this->x = mGameObject->transform.position.x;
        this->y = mGameObject->transform.position.y;
    }
}