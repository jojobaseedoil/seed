#pragma once

#include <SDL2/SDL_stdinc.h>

class GameObject;

class Component
{
public:
    friend class GameObject;

    virtual ~Component() = default;

    virtual void Update(float deltaTime);

protected:
    GameObject *mGameObject = nullptr;
};