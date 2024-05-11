#pragma once

#include "../Component.h"

class SDL_Renderer;

class DrawComponent : public Component
{
public:
    DrawComponent(GameObject *owner);

    virtual void draw(SDL_Renderer *renderer) = 0;

    /* check if is component visible */
    bool isVisible() const;
    
    /* set component visible/invisible */
    void setVisible();
    void setInvisible();

protected:
    bool mIsVisible;
};