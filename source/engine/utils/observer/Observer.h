#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <list>

class GameObject;

class Observer
{
public:
    Observer() = default;

    void subscribe(const std::string &layer, GameObject *entity);
    void unsubscribe(const std::string &layer, GameObject *entity);
    void notify(GameObject *entity, const std::vector<GameObject*> &responses);
    const std::list<GameObject*> &listenersOf(const std::string &layer) const;

private:
    std::unordered_map<std::string, std::list<GameObject*>> mListeners;
};