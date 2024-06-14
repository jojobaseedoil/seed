#include "GameObject.h"

#include "../scene/Scene.h"
#include <SDL2/SDL_log.h>

int GameObject::sNextId = 0;

GameObject::GameObject():
    mScene (nullptr),
    tag    (sNextId++),
    mState (State::Pending)
{
    transform = *AddComponent<Transform>();
}

GameObject::~GameObject()
{   
    CollisionSystem *csys = CollisionSystem::GetInstance();

    csys->RemoveScripts(tag);

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

/* GameObject state */
const GameObject::State &GameObject::GetState() const
{
    return mState;
}

void GameObject::Destroy(GameObject *entity)
{
    entity->mState = State::Destroy;
}

void GameObject::Activate(GameObject *entity)
{
    entity->mState = State::Active;
}

void GameObject::Pause(GameObject *entity)
{
    entity->mState = State::Paused;
}