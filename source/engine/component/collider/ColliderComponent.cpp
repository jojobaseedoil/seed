#include "ColliderComponent.h"

#include "../../entity/GameObject.h"

ColliderComponent::ColliderComponent(GameObject *owner): Component(owner)
{

}

void ColliderComponent::detectCollision(std::vector<ColliderComponent*> &colliders)
{
    /*
        decide what should I pass to the owner later
        and then, change onCollision() to onCollision(responses);
    */ 
    std::vector<ColliderComponent*> responses; 

    for(ColliderComponent *other : colliders)
    {
        if(!other->isEnabled() && other == nullptr)
        {
            continue;   
        }

        if(this->intersect(other))
        {
            responses.push_back(other);
        }
    }

    /* callback to resolve collisions */
    mOwner->onCollision();
}