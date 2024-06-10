#ifndef MONO_BEHAVIOUR_H
#define MONO_BEHAVIOUR_H

#include "Collider.h"

class MonoBehaviour : public Component
{
public:
    virtual void OnStart();
    virtual void OnUpdate();
    virtual void OnTriggerEnter(Collider &other);
    virtual void OnTriggerStay(Collider &other);
    virtual void OnTriggerExit(Collider &other);
    virtual void OnDestroy();
};

#endif // MONO_BEHAVIOUR_H