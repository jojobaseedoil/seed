#ifndef RENDER_H
#define RENDER_H

#include "Component.h"

#include <SDL2/SDL_render.h>

class Render : public Component
{
public:
    Render(SDL_Renderer *renderer);
    virtual ~Render();

    virtual void Draw();

protected:
    SDL_Renderer *mRenderer;
};

#endif // RENDER_H