#pragma once

#include "RigidBodyComponent.h"

#define GRAVITY   2000.0f
#define MAX_SPEED 800.0f

class RigidBody2DComponent : public RigidBodyComponent
{
public:
    RigidBody2DComponent(
        GameObject *owner, 
        float mass     = 1.0f, 
        float friction = 5.0f, 
        bool gravity   = false
    );

    /* euler method */
    void applyForce(const Vector2 &force) override;
    void update(float dt) override;

    /* enable disable gravity */
    void enableGravity();
    void disableGravity();

private:
    bool mGravity;
};