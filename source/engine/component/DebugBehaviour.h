#ifndef DEBUG_BEHAVIOUR_H
#define DEBUG_BEHAVIOUR_H

#include "MonoBehaviour.h"

#include <SDL2/SDL_log.h>

#include "../system/input/Keyboard.h"
#include "../game/Game.h"
#include "../entity/GameObject.h"

class DebugBehaviour : public MonoBehaviour
{
public:
    const float speed = 5000.0f;

    void OnStart() override
    {
        mRigidbody = mGameObject->GetComponent<RigidBody>();
        mKeyboard.Bind(SDL_SCANCODE_SPACE, [this](){ Attack(); });
    }

    void Update(float deltaTime) override
    {
        Move();
    }

    void Attack()
    {
        SDL_Log("Attacking...");
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

private:
    RigidBody *mRigidbody;
    Keyboard mKeyboard;
};

#endif // DEBUG_BEHAVIOUR_H