#include "Component.h"

#include <SDL2/SDL_log.h>

#include "../entity/GameObject.h"

Component::Component() : 
    mGameObject (nullptr)
{

}

void Component::Update(float deltaTime)
{

}

const Layer &Component::GetLayer() const
{
    return mGameObject->layer;
} 

int Component::GetTag() const
{
    return mGameObject->tag;
}