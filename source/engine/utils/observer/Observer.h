#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <list>

class GameObject;

/* this observer is looking for collisions */
class Observer
{
public:
    Observer() = default;

    /* add/remove 'entity' to the notification list */
    void subscribe(const std::string &layer, GameObject *entity);
    void unsubscribe(const std::string &layer, GameObject *entity);

    /* notify a list of entitys about the collision */
    void notify(GameObject *entity, const std::vector<GameObject*> &responses);

    /* get all entities of a certain layer */  
    const std::list<GameObject*> &listenersOf(const std::string &layer) const;

private:
    /* 'Observer' params */
    std::unordered_map<std::string, std::list<GameObject*>> mListeners;
};