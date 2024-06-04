#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL_stdinc.h>

class GameObject;

enum Layer
{
    Instances,
    Background,
    Wall
};

class Component
{
public:
    friend class GameObject;
    Component();
    virtual ~Component() = default;

    virtual void Update(float deltaTime);

    /* GameObject info */
    const Layer &GetLayer() const; 
    int GetTag() const;

protected:
    GameObject *mGameObject;
};

#endif // COMPONENT_H