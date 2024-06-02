#include "GameObject.h"

#include <SDL2/SDL_log.h>

GameObject::GameObject():
    mScene(nullptr)
{
    transform = *AddComponent<Transform>();
}

GameObject::~GameObject()
{
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