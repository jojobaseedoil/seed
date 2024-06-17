#include "GameObject.h"

#include "../scene/Scene.h"
#include <SDL2/SDL_log.h>

int GameObject::sNextId = 0;

GameObject::GameObject(Scene *scene):
    mScene (scene),
    tag    (sNextId++),
    mState (State::Active)
{
    /* insert this entity into current scene */
    SceneManager *manager = SceneManager::GetInstance();
    manager->InsertEntity(this);

    transform = *AddComponent<Transform>();
}

GameObject::~GameObject()
{   
    /* remove this entity from collision system */  
    CollisionSystem *csys = CollisionSystem::GetInstance();
    csys->RemoveScripts(tag);

    /* remove this entity from current scene */
    SceneManager *manager = SceneManager::GetInstance();
    manager->RemoveEntity(this);

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