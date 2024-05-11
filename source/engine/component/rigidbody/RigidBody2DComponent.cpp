#include "RigidBody2DComponent.h"

#include "../../entity/GameObject.h"

RigidBody2DComponent::RigidBody2DComponent(
    GameObject *owner, 
    float mass,
    float friction, 
    bool gravity
):
    RigidBodyComponent (owner, mass, friction),
    mGravity           (gravity)
{

}

/* euler method */
void RigidBody2DComponent::applyForce(const Vector2 &force)
{
    mAcceleration += force * (1.0f/mMass);
}

void RigidBody2DComponent::update(float dt)
{
    // Apply friction
    if(mVelocity.x != 0.0f) {
        applyForce(Vector2::UnitX * -mFriction * mVelocity.x);
    }
    if(mVelocity.y != 0.0f) {
        applyForce(Vector2::UnitY * -mFriction * mVelocity.y);
    }

    // Apply gravity
    if(mGravity == true)
    {
        applyForce(Vector2::UnitY * GRAVITY);
    }

    // Euler Integration
    mVelocity += mAcceleration * dt;

    /* clamp speed */
    mVelocity.x = Math::Clamp<float>(mVelocity.x, -MAX_SPEED, MAX_SPEED);
    mVelocity.y = Math::Clamp<float>(mVelocity.y, -GRAVITY, GRAVITY);

    if(Math::NearZero(mVelocity.x, 1.0f)) {
        mVelocity.x = 0.f;
    }
    if(Math::NearZero(mVelocity.y, 1.0f)) {
        mVelocity.y = 0.f;
    }

    Vector2 position = mOwner->position();
    mOwner->translate(mVelocity * dt);

    mAcceleration.Set(0.f, 0.f);
}

/* enable disable gravity */
void RigidBody2DComponent::enableGravity()
{
    mGravity = true;
}

void RigidBody2DComponent::disableGravity()
{
    mGravity = false;
}