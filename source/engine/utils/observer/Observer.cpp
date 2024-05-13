#include "Observer.h"

#include "../../entity/GameObject.h"

void Observer::subscribe(const std::string &layer, GameObject *entity)
{
    mListeners[layer].push_back(entity);
}

void Observer::unsubscribe(const std::string &layer, GameObject *entity)
{
    mListeners[layer].remove(entity);
}

void Observer::notify(GameObject *entity, const std::vector<GameObject*> &responses)
{
    for(GameObject *other : responses)
    {
        entity->onCollision(other);
    }
}

const std::list<GameObject*> &Observer::listenersOf(const std::string &layer) const
{
    auto it = mListeners.find(layer);

    if (it != mListeners.end()) 
    {
        return it->second;
    } 

    static std::list<GameObject*> emptyList;
    return emptyList;
}