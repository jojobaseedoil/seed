#ifndef BOX_BEHAVIOUR_H
#define BOX_BEHAVIOUR_H

#include "MonoBehaviour.h"

#include <SDL2/SDL_log.h>

#include "../system/collision/CollisionSystem.h"
#include "../system/sound/AudioSystem.h"
#include "../system/input/Keyboard.h"
#include "../entity/GameObject.h"

class BoxBehaviour : public MonoBehaviour
{
public:

    void OnStart() override
    {
        sCsys     = CollisionSystem::GetInstance();
        mCollider = mGameObject->GetComponent<Collider>();        
    }

    void Update(float deltaTime) override
    {
        sCsys->BroadPhaseCollisionDetection(mCollider);
    }

private:
    CollisionSystem *sCsys;
    Collider        *mCollider;
};

#endif // BOX_BEHAVIOUR_H