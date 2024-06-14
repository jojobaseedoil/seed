#ifndef DEBUG_BEHAVIOUR_H
#define DEBUG_BEHAVIOUR_H

#include "MonoBehaviour.h"

#include <SDL2/SDL_log.h>

#include "../system/collision/CollisionSystem.h"
#include "../system/sound/AudioSystem.h"
#include "../system/input/Keyboard.h"
#include "../entity/GameObject.h"

class DebugBehaviour : public MonoBehaviour
{
public:
    const float speed = 5000.0f;

    void OnStart() override
    {
        sCollisionSystem = CollisionSystem::GetInstance();
        
        mRigidbody = mGameObject->GetComponent<RigidBody>();
        mCollider  = mGameObject->GetComponent<Collider>();
        
        mKeyboard.Bind(SDL_SCANCODE_SPACE, [this](){ DestroySelf(); });
    }

    void Update(float deltaTime) override
    {
        mAudio.Update(deltaTime);
        Move();

        sCollisionSystem->BroadPhaseCollisionDetection(mCollider);
    }

    void DestroySelf()
    {
        GameObject::Destroy(mGameObject);
    }

    void Move()
    {
        if(mRigidbody != nullptr)
        {
            mRigidbody->ApplyForce( Direction() * speed);
        }
    }

    Vector2 Direction()
    {   
        float x = 0.0f;
        float y = 0.0f;
        
        if( mKeyboard.IsPressed(SDL_SCANCODE_A) )
        {
            x = -1.0f;
        }
        else if( mKeyboard.IsPressed(SDL_SCANCODE_D) )
        {
            x = 1.0f;
        }

        if( mKeyboard.IsPressed(SDL_SCANCODE_W) )
        {
            y = -1.0f;
        }
        else if( mKeyboard.IsPressed(SDL_SCANCODE_S) )
        {
            y = 1.0f;
        }

        return Vector2(x,y);
    }

    void OnTriggerEnter(Collider &other) override
    {
        mAudio.PlaySound("enter.wav");
    }

    void OnTriggerExit(Collider &other) override
    {
        mAudio.PlaySound("exit.wav");
    }

private:
    RigidBody *mRigidbody;
    Collider *mCollider;
    Keyboard mKeyboard;
    AudioSystem mAudio;
    CollisionSystem *sCollisionSystem;
};

#endif // DEBUG_BEHAVIOUR_H