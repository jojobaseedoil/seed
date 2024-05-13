#include "ColliderComponent.h"

#include "../../entity/GameObject.h"


ColliderComponent::ColliderComponent(GameObject *owner, Observer *obs):
    Component (owner),
    mObserver (obs)
{

}

void ColliderComponent::update(float dt)
{
    std::vector<GameObject*> responses;

    for(const std::string &layer : mLayers)
    {
        scan(layer, responses);
    }

    mObserver->notify(mOwner, responses);
}

void ColliderComponent::scan(const std::string &layer, std::vector<GameObject*> &responses)
{
    std::list<GameObject*> listeners = mObserver->listenersOf(layer);

    for(GameObject *other : listeners)
    {
        if(intersect(other))
        {
            responses.push_back(other);
        }
    }
}

void ColliderComponent::addLayersFrom(const std::vector<std::string> &layers)
{
    for(const std::string &layer : layers)
    {
        mLayers.push_back(layer);
    }
}