#pragma once

#include "../Component.h"
#include "../../utils/Math.h"

class RigidBodyComponent : public Component
{
public:
    RigidBodyComponent(GameObject *owner, float mass=1.0f, float friction=12.5f);
    
    virtual void applyForce(const Vector2 &force) = 0;

    const Vector2 &getVelocity() const;
    void setVelocity(const Vector2 &velocity);

    const Vector2 &getAcceleration() const;
    void setAcceleration(const Vector2 &acceleration);

protected:
    Vector2 mVelocity;
    Vector2 mAcceleration;

    float mFriction;
    float mMass;
};