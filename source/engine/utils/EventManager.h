#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <vector>
#include <functional>

class MonoBehaviour;
class Collider;

class EventManager
{
public:
    using TriggerEvent = std::function<void(Collider&)>;

    void Register(MonoBehaviour* component);
    void Unregister(MonoBehaviour* component);

    void OnTriggerStay(Collider& collider);
    void OnTriggerEnter(Collider& collider);
    void OnTriggerExit(Collider& collider);

private:
    std::vector<MonoBehaviour*> mScripts;
};

#endif // EVENT_MANAGER_H