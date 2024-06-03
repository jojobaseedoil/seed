#ifndef COMPONENT_H
#define COMPONENT_H

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

#endif // COMPONENT_H