#include "BoxCollider.h"

#include "../entity/GameObject.h"
#include "RigidBody.h"

#include <SDL2/SDL_log.h>

BoxCollider::BoxCollider(float w, float h, bool isTrigger):
    Collider (isTrigger),
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

    if (!box || this->isTrigger || box->isTrigger)
    {
        return;
    }

    RigidBody *rb1 = mGameObject->GetComponent<RigidBody>();
    RigidBody *rb2 = box->mGameObject->GetComponent<RigidBody>();

    // Calculate overlap on both axes
    float overlapX = std::min(x + w, box->x + box->w) - std::max(x, box->x);
    float overlapY = std::min(y + h, box->y + box->h) - std::max(y, box->y);

    // Find the minimum translation distance (MTD)
    if(overlapX < overlapY)
    {
        x      += (x < box->x ? -overlapX/2 :  overlapX/2);
        box->x += (x < box->x ?  overlapX/2 : -overlapX/2);
    }
    else
    {
        y      += (y < box->y ? -overlapY/2 :  overlapY/2);
        box->y += (y < box->y ?  overlapY/2 : -overlapY/2);
    }    

    // Update positions in the associated game objects
    if(mGameObject)
    {
        mGameObject->transform.position.x = this->x;
        mGameObject->transform.position.y = this->y;
    }

    if(box->mGameObject && rb2 && rb2->GetMass() != Math::Infinity)
    {
        box->mGameObject->transform.position.x = box->x;
        box->mGameObject->transform.position.y = box->y;
    }

    if(rb1 && rb2)
    {
        Vector2 relativeVelocity = rb2->GetVelocity() - rb1->GetVelocity();
        Vector2 normal = (overlapX < overlapY) ? Vector2::UnitX : Vector2::UnitY;
        float velAlongNormal =  Vector2::Dot(relativeVelocity, normal);

        if(velAlongNormal > 0)
        {
            return;
        } 
        
        /* Perfectly elastic collision */
        float restitution = 1.0f;
        float impulseScalar = -(1 + restitution) * velAlongNormal / (1 / rb1->GetMass() + 1 / rb2->GetMass());

        Vector2 impulse = impulseScalar * normal;
        rb1->SetVelocity(rb1->GetVelocity() - impulse * (1 / rb1->GetMass()));
        rb2->SetVelocity(rb2->GetVelocity() + impulse * (1 / rb2->GetMass()));
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