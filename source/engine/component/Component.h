#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL_stdinc.h>

class GameObject;

class Component
{
public:
    friend class GameObject;
    Component();
    virtual ~Component() = default;

    virtual void Update(float deltaTime);

    GameObject *mGameObject;
};

#endif // COMPONENT_H