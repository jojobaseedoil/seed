#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Component.h"
#include "../utils/Math.h"

#define GRAVITY   2000.0f
#define MAX_SPEED 800.0f

class RigidBody : public Component
{
public:
    RigidBody(float mass, float friction, bool isGravity);

    /* euler method */
    void ApplyForce(const Vector2 &force);
    void Update(float deltaTime) override;

    const float GetMass() const;
    const Vector2 &GetVelocity() const;
    void SetVelocity(const Vector2 &velocity);

private:
    Vector2 mVelocity;
    Vector2 mAcceleration;

    bool mIsGravity;
    
    float mFriction;
    float mMass;
};

#endif // RIGIDBODY_H