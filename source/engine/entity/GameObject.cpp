#include "GameObject.h"

#include "../component/Component.h"

#include <iostream>

GameObject::GameObject(Scene *scene):
    mScene     (scene),
    mTransform (Transform()),
    mState     (State::Active)
{
    std::cout << "\t\tcreate 'GameObject'.\n";
}

GameObject::~GameObject()
{
    std::cout << "\t\tdelete 'GameObject'.\n";

    for(Component *c : mComponents)
    {
        delete c;
    }
}


/* update game object */
void GameObject::processInput(const Uint8 *keyboard)
{
    if(mState == State::Active)
    {
        for(Component *c : mComponents)
        {
            if(c->isEnabled())
            {
                c->processInput(keyboard);
            }
        }

        onProcessInput(keyboard);
    }
}

void GameObject::update(float dt)
{
    if(mState == State::Active)
    {
        for(Component *c : mComponents)
        {
            if(c->isEnabled())
            {
                c->update(dt);
            }
        }

        onUpdate(dt);
    }
}

/* transform setters */
void GameObject::translate(const Vector2 &p)
{
    mTransform.position.x += p.x;
    mTransform.position.y += p.y;
}

void GameObject::rotate(const Vector2 &r)
{
    mTransform.rotation.x = (float)((int)(mTransform.rotation.x + (r.x < 0 ? r.x + 360.0f : r.x)) % 360);
    mTransform.rotation.y = (float)((int)(mTransform.rotation.y + (r.y < 0 ? r.y + 360.0f : r.y)) % 360);
}

void GameObject::scale(const Vector2 &s)
{
    mTransform.scale.x *= s.x;
    mTransform.scale.y *= s.y;
}

/* transform getters */
const Vector2 &GameObject::position() const
{
    return mTransform.position;
}

const Vector2 &GameObject::rotation() const
{
    return mTransform.rotation;
}

const Vector2 &GameObject::scale() const
{
    return mTransform.scale;
}

/* gameObject state */
void GameObject::setState(const State &state)
{   
    mState = state;
}

const State &GameObject::getState() const
{
    return mState;
}

/* insert component into 'this' GameObject */
void GameObject::plug(Component *c)
{
    mComponents.push_back(c);
}

/* specific collision check */
void GameObject::detectCollision()
{
    
}

void GameObject::onCollision()
{

}

/* specific update */
void GameObject::onProcessInput(const Uint8 *keyboard)
{

}

void GameObject::onUpdate(float dt)
{

}
