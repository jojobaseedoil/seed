#pragma once

#include <string>

#include "DrawComponent.h"

#define SPRITE_8   8
#define SPRITE_16  16
#define SPRITE_32  32
#define SPRITE_64  64
#define SPRITE_128 128
#define SPRITE_256 256

class SDL_Texture;

class Sprite : public DrawComponent
{
public:
    Sprite(
        GameObject *owner, 
        const std::string &sprite = "../assets/sprites/notex.jpg", 
        Uint16 sprWidth           = SPRITE_32, 
        Uint16 sprHeight          = SPRITE_32
    );

    void draw(SDL_Renderer *renderer) override;

protected:
    static SDL_Texture *loadTexure(SDL_Renderer *renderer, const std::string &tex);

    /* sprite info. */
    SDL_Texture *mSprTexture;
    std::string mSprPath;
    Uint8 mSprWidth;
    Uint8 mSprHeight;
};