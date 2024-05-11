#include "RigidBodyComponent.h"

RigidBodyComponent::RigidBodyComponent(GameObject *owner, float mass, float friction):
    Component     (owner),
    mVelocity     (Vector2::Zero),
    mAcceleration (Vector2::Zero),
    mFriction     (friction),
    mMass         (mass)
{

}

const Vector2 &RigidBodyComponent::getVelocity() const
{
    return mVelocity;
}

void RigidBodyComponent::setVelocity(const Vector2 &velocity)
{
    mVelocity = velocity;
}

const Vector2 &RigidBodyComponent::getAcceleration() const
{
    return mAcceleration;
}

void RigidBodyComponent::setAcceleration(const Vector2 &acceleration)
{
    mAcceleration = acceleration;
}