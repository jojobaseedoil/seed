#include "GameObject.h"

#include "../scene/Scene.h"
#include <SDL2/SDL_log.h>

int GameObject::sNextId = 0;

GameObject::GameObject(const Layer &layer):
    mScene (nullptr),
    layer  (layer),
    tag    (sNextId++),
    mState (State::Pending)
{
    transform = *AddComponent<Transform>();
}

GameObject::~GameObject()
{   
    CollisionSystem *csys = CollisionSystem::GetInstance();

    if(csys != nullptr)
    {
        csys->RemoveScripts(tag);
    }

    if(mScene != nullptr)
    {
        mScene->RemoveEntity(this);
    }

    for(Component *c : mComponents)
    {
        delete c;
    }
}

void GameObject::Update(float deltaTime)
{
    for(Component *c : mComponents)
    {
        c->Update(deltaTime);
    }
}

void GameObject::Destroy(GameObject *entity)
{
    delete entity;
}

/* GameObject state */
const GameObject::State &GameObject::GetState() const
{
    return mState;
}

void GameObject::SetState(const State &newState)
{    
    mState = newState;
}