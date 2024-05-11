#pragma once

#include <SDL2/SDL_stdinc.h>

class GameObject;

class Component
{
public:
    Component(GameObject *owner);
    virtual ~Component();

    /* update component */
    virtual void processInput(const Uint8 *keyboard);
    virtual void update(float dt);

    /* check if component is enabled */
    bool isEnabled() const;
    
    /* enable/disable component */
    void enable();
    void disable();

protected:
    /* 'Component' params */
    GameObject *mOwner;
    bool mIsEnabled;
};