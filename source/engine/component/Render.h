#ifndef RENDER_H
#define RENDER_H

#include "Component.h"

#include <SDL2/SDL_render.h>

class Render : public Component
{
public:
    Render(SDL_Renderer *renderer);

    virtual void Draw();
    virtual void Update(float deltaTime) override;

protected:
    SDL_Renderer *mRenderer;
};

#endif // RENDER_H