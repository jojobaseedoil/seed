#include "BoxCollider.h"

#include "../entity/GameObject.h"

#include <SDL2/SDL_log.h>

BoxCollider::BoxCollider(float w, float h):
    x(0.0f),
    y(0.0f),
    w(w), 
    h(h)
{

}
#include <iostream>
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

void BoxCollider::Update(float deltaTime)
{
    if(mGameObject)
    {
        this->x = mGameObject->transform.position.x;
        this->y = mGameObject->transform.position.y;
    }
}