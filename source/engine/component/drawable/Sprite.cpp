#include "Sprite.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_log.h>

#include "../../entity/GameObject.h"

Sprite::Sprite(
    GameObject *owner, 
    const std::string &sprite,
    Uint16 sprWidth, 
    Uint16 sprHeight
):
    DrawComponent (owner),
    mSprTexture   (nullptr),
    mSprPath      (sprite),
    mSprWidth     (sprWidth),
    mSprHeight    (sprHeight)
{

}

void Sprite::draw(SDL_Renderer *renderer)
{
    if(mSprTexture == nullptr)
    {
        mSprTexture = loadTexure(renderer, mSprPath);
    }

    const Vector2 pos   = mOwner->position();
    const Vector2 rot   = mOwner->rotation();
    const Vector2 scale = mOwner->scale();

    SDL_Rect dstRect = {
        static_cast<int>(pos.x),
        static_cast<int>(pos.y),
        static_cast<int>(mSprWidth  * abs(scale.x)),
        static_cast<int>(mSprHeight * abs(scale.y))
    };

    SDL_Point center = {mSprWidth/2, mSprHeight/2};

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    SDL_RenderCopyEx(
        renderer,
        mSprTexture,
        nullptr,
        &dstRect,
        rot.x,
        &center,
        flip
    );
}


SDL_Texture *Sprite::loadTexure(SDL_Renderer *renderer, const std::string &tex)
{
    SDL_Surface *surface = IMG_Load(tex.c_str());

    if(surface == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Fail to load %s surface.\n", tex.c_str());
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if(texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Fail to load %s texture.\n", tex.c_str());
        return nullptr;
    }

    return texture;
}