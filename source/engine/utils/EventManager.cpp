#include "EventManager.h"

#include "../component/MonoBehaviour.h"
#include "../component/Collider.h"
#include <algorithm>

void EventManager::Register(MonoBehaviour* script)
{
    mScripts.push_back(script);
}

void EventManager::Unregister(MonoBehaviour* script)
{
    mScripts.erase(std::remove(mScripts.begin(), mScripts.end(), script), mScripts.end());
}
    
void EventManager::OnTriggerStay(Collider& collider)
{
    for(MonoBehaviour *script : mScripts)
    {
        script->OnTriggerStay(collider);
    }
}

void EventManager::OnTriggerEnter(Collider& collider)
{
    for(MonoBehaviour *script : mScripts)
    {
        script->OnTriggerEnter(collider);
    }
}

void EventManager::OnTriggerExit(Collider& collider)
{
    for(MonoBehaviour *script : mScripts)
    {
        script->OnTriggerExit(collider);
    }
}