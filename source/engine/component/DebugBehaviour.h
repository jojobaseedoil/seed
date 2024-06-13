#ifndef DEBUG_BEHAVIOUR_H
#define DEBUG_BEHAVIOUR_H

#include "MonoBehaviour.h"

#include <SDL2/SDL_log.h>

#include "../system/sound/AudioSystem.h"
#include "../system/input/Keyboard.h"
#include "../entity/GameObject.h"

class DebugBehaviour : public MonoBehaviour
{
public:
    const float speed = 5000.0f;

    void OnStart() override
    {
        mAudio = new AudioSystem;
        mRigidbody = mGameObject->GetComponent<RigidBody>();
        mKeyboard.Bind(SDL_SCANCODE_SPACE, [this](){ DestroySelf(); });
    }

    void Update(float deltaTime) override
    {
        mAudio->Update(deltaTime);
        Move();
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
        SDL_Log("Enter");
        mAudio->PlaySound("enter.wav");
    }

    void OnTriggerExit(Collider &other) override
    {
        SDL_Log("Exit");
        mAudio->PlaySound("exit.wav");
    }

private:
    RigidBody *mRigidbody;
    Keyboard mKeyboard;
    AudioSystem *mAudio;
};

#endif // DEBUG_BEHAVIOUR_H