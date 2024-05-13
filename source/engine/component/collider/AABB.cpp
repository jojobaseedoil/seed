#include "AABB.h"

#include <SDL2/SDL_log.h>

#include "../../entity/GameObject.h"
#include "../../component/rigidbody/RigidBody2DComponent.h"

AABB::AABB(GameObject *owner, Observer *obs, float w, float h):
    ColliderComponent (owner, obs),
    mAABB             ({0,0,w,h})
{

}

bool AABB::intersect(GameObject *other)
{
    auto collider = other->getComponent<AABB>();
    
    if( collider == nullptr || !collider->isEnabled() || this == collider)
    {
        return false;
    }

    return max().x > collider->min().x &&
           min().x < collider->max().x &&
           min().y < collider->max().y &&
           max().y > collider->min().y;
}

void AABB::resolve(GameObject *other)
{
    AABB *collider;
    collider = other->getComponent<AABB>();

    RigidBody2DComponent *rigidbody;
    rigidbody = mOwner->getComponent<RigidBody2DComponent>();

    if(rigidbody == nullptr)
    {
        return;
    }

    const int LEFT  = 0;
    const int RIGHT = 1;
    const int TOP   = 2;
    const int DOWN  = 3;

    /* get min overlap */
    std::unordered_map<int, double> overlap;
    
    overlap[LEFT]   = collider->max().x - min().x;
    overlap[RIGHT]  = collider->min().x - max().x;
    overlap[TOP] = collider->max().y - min().y;
    overlap[DOWN]  = collider->min().y - max().y;

    double dist = overlap[LEFT];
    int    side = LEFT;

    for(int i=1; i<4; i++)
    {
        if( abs(overlap[i]) < abs(dist) )
        {
            dist = overlap[i];
            side = i;
        }
    }

    /* apply the collision */
    Vector2 vel = rigidbody->getVelocity();
    Vector2 pos = mOwner->position();

    if(vel.y > 0.0f && side==DOWN || vel.y < 0.0f && side==TOP)
    {
        pos.x = 0.0f;
        pos.y = dist;
        
        vel.y = 0.0f;
    }
    else if(vel.x > 0.0f && side==RIGHT || vel.x < 0.0f && side==LEFT)
    {
        pos.x = dist;
        pos.y = 0.0f;

        vel.x = 0.0f;
    }

    mOwner->translate(pos);
    rigidbody->setVelocity(vel);
}

Vector2 AABB::min() const
{
    Vector2 pos = mOwner->position();

    return Vector2(mAABB.x + pos.x, mAABB.y + pos.y);
}

Vector2 AABB::max() const
{
    return Vector2( min().x + mAABB.w, min().y + mAABB.h );
}

Vector2 AABB::center() const
{
    return Vector2( min().x + mAABB.w/2.0f, min().y + mAABB.h/2.0f );
}