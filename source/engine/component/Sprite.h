#ifndef SPRITE_H
#define SPRITE_H

#include "Render.h"

#include <string>

class Sprite : public Render
{
public:
    Sprite(SDL_Renderer *renderer, const std::string &sprite="../assets/sprites/notex.png");

    void Draw() override;

    static SDL_Texture *LoadTexture(SDL_Renderer *renderer, const std::string &sprite);

private:
    SDL_Texture *mTexture;
};

#endif // SPRITE_H