#include "BoxCollider.h"

#include "../entity/GameObject.h"

BoxCollider::BoxCollider(float x, float y, float w, float h):
    x(x), y(y),
    w(w), h(h)
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

void BoxCollider::Update(float deltaTime)
{
    this->x = mGameObject->transform.position.x;
    this->y = mGameObject->transform.position.y;
}