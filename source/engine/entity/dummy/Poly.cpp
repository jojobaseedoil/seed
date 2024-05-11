#include "Poly.h"

#include <SDL2/SDL.h>

#include "../../component/rigidbody/RigidBody2DComponent.h"

Poly::Poly(
    Scene *scene, 
    const std::vector<Vector2> &vertices, 
    const Color &col
):
    GameObject (scene),
    mVertices  (vertices),
    mColor     (col)
{
    
}

void Poly::onProcessInput(const Uint8 *keyboard)
{
    auto rigidbody = this->getComponent<RigidBody2DComponent>();

    if(rigidbody == nullptr)
        return;

    Vector2 vel = rigidbody->getVelocity();
    bool pressedMovementKey = false;

    vel.x = 0.0f;
    vel.y = 0.0f;

    if (keyboard[SDL_SCANCODE_D])
    {
        pressedMovementKey = true;
        vel.x = 1.0f;
    }
    else if (keyboard[SDL_SCANCODE_A])
    {

        pressedMovementKey = true;
        vel.x = -1.0f;
    }

    if (keyboard[SDL_SCANCODE_W])
    {
        pressedMovementKey = true;
        vel.y = -1.0f;
    }
    else if (keyboard[SDL_SCANCODE_S])
    {
        pressedMovementKey = true;
        vel.y = 1.0f;
    }

    if(keyboard[SDL_SCANCODE_E])
    {
        rotate(Vector2(32,0));
    }
    else if(keyboard[SDL_SCANCODE_Q])
    {
        rotate(Vector2(-32,0));
    }

    if(keyboard[SDL_SCANCODE_F])
    {
        scale(Vector2(1.25,1.25));
    }
    else if(keyboard[SDL_SCANCODE_G])
    {
        scale(Vector2(0.75,0.75));
    }

    if(pressedMovementKey)
    {
        vel.Normalize();
        rigidbody->applyForce(vel*5000);
    }
}