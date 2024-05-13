#include "Poly.h"

#include <SDL2/SDL.h>

#include "../scene/PolyScene.h"

Poly::Poly(
    Scene *scene, 
    const std::string &layer,
    const std::vector<Vector2> &vertices, 
    const Color &col
):
    GameObject (scene, layer),
    mVertices  (vertices),
    mColor     (col)
{
    
}

void Poly::onProcessInput(const Uint8 *keyboard)
{
    RigidBody2DComponent *rigidbody;
    rigidbody = getComponent<RigidBody2DComponent>();

    if(rigidbody == nullptr)
    {
        return;
    }

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

#include <iostream>
void Poly::onCollision(GameObject *other)
{
    AABB *collider;
    collider = getComponent<AABB>();

    if(collider != nullptr)
    {
        collider->resolve(other);
    }
}