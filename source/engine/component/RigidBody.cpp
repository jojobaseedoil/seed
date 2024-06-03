#include "RigidBody.h"

#include "../entity/GameObject.h"

#include <SDL2/SDL_log.h>

RigidBody::RigidBody(float mass, float friction, bool isGravity):
    mVelocity     (Vector2::Zero),
    mAcceleration (Vector2::Zero),
    mMass         (mass != 0.0f ? mass : 1e-9),
    mFriction     (friction),
    mIsGravity    (isGravity)
{

}

void RigidBody::ApplyForce(const Vector2 &force)
{
    mAcceleration += force * (1.0f / mMass);
}

void RigidBody::Update(float deltaTime)
{
    if(mIsGravity == true)
    {
        ApplyForce(Vector2::UnitY * GRAVITY);
    }

    // Apply friction
    if(mVelocity.x != 0.0f) {
        ApplyForce(Vector2::UnitX * -mFriction * mVelocity.x);
    }
    if(mVelocity.y != 0.0f) {
        ApplyForce(Vector2::UnitY * -mFriction * mVelocity.y);
    }

    // Euler Integration
    mVelocity += mAcceleration * deltaTime;

    /* clamp speed */
    mVelocity.x = Math::Clamp<float>(mVelocity.x, -MAX_SPEED, MAX_SPEED);
    mVelocity.y = Math::Clamp<float>(mVelocity.y, -GRAVITY, GRAVITY);

    if(Math::NearZero(mVelocity.x, 1.0f)) {
        mVelocity.x = 0.0f;
    }
    if(Math::NearZero(mVelocity.y, 1.0f)) {
        mVelocity.y = 0.0f;
    }

    mGameObject->transform.position += mVelocity * deltaTime;

    mAcceleration.Set(0.0f, 0.0f);
}


const float RigidBody::GetMass() const
{
    return mMass;
}

const Vector2 &RigidBody::GetVelocity() const
{
    return mVelocity;
}

void RigidBody::SetVelocity(const Vector2 &velocity)
{
    mVelocity = velocity;
}