#include "GameObject.h"

#include <SDL2/SDL_log.h>

GameObject::GameObject(const std::string &layer):
    mScene    (nullptr),
    layer     (layer)
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