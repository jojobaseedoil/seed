#include "Component.h"

#include <SDL2/SDL_log.h>

#include "../entity/GameObject.h"

Component::Component(GameObject *owner):
    mOwner     (owner),
    mIsEnabled (true)
{
    SDL_Log("\t\t\tcreate 'Component'.\n");
}

Component::~Component()
{
    SDL_Log("\t\t\tdelete 'Component'.\n");
}

/* update component */
void Component::processInput(const Uint8 *keyboard)
{

}

void Component::update(float dt)
{

}

/* check if component is enabled */
bool Component::isEnabled() const
{
    return mIsEnabled;
}

/* enable/disable component */
void Component::enable()
{   
    mIsEnabled = true;
}

void Component::disable()
{   
    mIsEnabled = false;
}